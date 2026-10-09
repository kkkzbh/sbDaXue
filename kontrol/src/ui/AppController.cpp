#include "ui/AppController.h"

#include <QtCore/QProcess>
#include <QtCore/QVariantMap>

#include <array>
#include <optional>
#include <ranges>

namespace {

enum struct CompletionAction : std::uint8_t {
  None,
  Logout,
  Reboot,
  Unknown,
};

auto to_variant(kontrol::ModeOption const& mode) -> QVariantMap {
  auto map = QVariantMap {};
  map.insert(QStringLiteral("rawMode"), QVariant::fromValue(mode.raw_mode));
  map.insert(QStringLiteral("id"), QString::fromStdString(mode.id));
  map.insert(QStringLiteral("label"), QString::fromStdString(mode.label));
  map.insert(QStringLiteral("supported"), mode.supported);
  return map;
}

auto normalize_mode(std::uint32_t raw_mode) -> std::uint32_t {
  return raw_mode;
}

auto mode_name_qt(std::uint32_t raw_mode) -> QString {
  return QString::fromStdString(kontrol::mode_label(normalize_mode(raw_mode)));
}

auto mode_switch_hint(std::uint32_t from_mode, std::uint32_t to_mode) -> QString {
  auto const from = normalize_mode(from_mode);
  auto const to = normalize_mode(to_mode);

  if (from == to) {
    return QStringLiteral("当前已经是该模式。");
  }

  if (from == kontrol::mode::asus_mux_dgpu && to == kontrol::mode::hybrid) {
    return QStringLiteral("从独显直连切到混合模式时，系统可能立即结束占用 NVIDIA 的进程，并需要重启完成切换。");
  }

  if (from == kontrol::mode::asus_mux_dgpu && to == kontrol::mode::integrated) {
    return QStringLiteral("从独显直连切到集显模式时，系统可能立即结束占用 NVIDIA 的进程，并需要重启完成切换。");
  }

  if (from == kontrol::mode::hybrid && to == kontrol::mode::integrated) {
    return QStringLiteral("从混合模式切到集显模式通常需要注销完成切换。");
  }

  if (from == kontrol::mode::integrated && to == kontrol::mode::hybrid) {
    return QStringLiteral("从集显模式切到混合模式通常需要注销完成切换。");
  }

  if (from == kontrol::mode::hybrid && to == kontrol::mode::asus_mux_dgpu) {
    return QStringLiteral("从混合模式切到独显直连通常需要重启完成切换。");
  }

  if (from == kontrol::mode::integrated && to == kontrol::mode::asus_mux_dgpu) {
    return QStringLiteral("从集显模式切到独显直连通常需要重启完成切换。");
  }

  return QStringLiteral("此切换可能触发注销或重启，请先保存所有工作。");
}

auto completion_action_from_transition(std::uint32_t from_mode, std::uint32_t to_mode) -> CompletionAction {
  auto const from = normalize_mode(from_mode);
  auto const to = normalize_mode(to_mode);

  switch (to) {
  case kontrol::mode::hybrid:
    switch (from) {
    case kontrol::mode::integrated:
    case kontrol::mode::asus_egpu:
      return CompletionAction::Logout;
    case kontrol::mode::asus_mux_dgpu:
      return CompletionAction::Reboot;
    case kontrol::mode::vfio:
      return CompletionAction::Unknown;
    case kontrol::mode::nvidia_no_modeset:
    case kontrol::mode::hybrid:
    case kontrol::mode::unknown:
      return CompletionAction::None;
    default:
      return CompletionAction::Unknown;
    }
  case kontrol::mode::integrated:
    switch (from) {
    case kontrol::mode::hybrid:
    case kontrol::mode::asus_egpu:
      return CompletionAction::Logout;
    case kontrol::mode::asus_mux_dgpu:
      return CompletionAction::Reboot;
    case kontrol::mode::vfio:
    case kontrol::mode::nvidia_no_modeset:
    case kontrol::mode::integrated:
    case kontrol::mode::unknown:
      return CompletionAction::None;
    default:
      return CompletionAction::Unknown;
    }
  case kontrol::mode::nvidia_no_modeset:
    switch (from) {
    case kontrol::mode::asus_egpu:
      return CompletionAction::Logout;
    case kontrol::mode::asus_mux_dgpu:
      return CompletionAction::Reboot;
    case kontrol::mode::integrated:
    case kontrol::mode::nvidia_no_modeset:
    case kontrol::mode::vfio:
    case kontrol::mode::hybrid:
    case kontrol::mode::unknown:
      return CompletionAction::None;
    default:
      return CompletionAction::Unknown;
    }
  case kontrol::mode::vfio:
    switch (from) {
    case kontrol::mode::asus_egpu:
    case kontrol::mode::hybrid:
      return CompletionAction::Logout;
    case kontrol::mode::asus_mux_dgpu:
      return CompletionAction::Reboot;
    case kontrol::mode::integrated:
    case kontrol::mode::vfio:
    case kontrol::mode::nvidia_no_modeset:
    case kontrol::mode::unknown:
      return CompletionAction::None;
    default:
      return CompletionAction::Unknown;
    }
  case kontrol::mode::asus_egpu:
    switch (from) {
    case kontrol::mode::integrated:
    case kontrol::mode::hybrid:
    case kontrol::mode::nvidia_no_modeset:
      return CompletionAction::Logout;
    case kontrol::mode::vfio:
      return CompletionAction::Unknown;
    case kontrol::mode::asus_mux_dgpu:
      return CompletionAction::Reboot;
    case kontrol::mode::asus_egpu:
    case kontrol::mode::unknown:
      return CompletionAction::None;
    default:
      return CompletionAction::Unknown;
    }
  case kontrol::mode::asus_mux_dgpu:
    switch (from) {
    case kontrol::mode::hybrid:
    case kontrol::mode::integrated:
    case kontrol::mode::nvidia_no_modeset:
    case kontrol::mode::vfio:
    case kontrol::mode::asus_egpu:
      return CompletionAction::Reboot;
    case kontrol::mode::asus_mux_dgpu:
    case kontrol::mode::unknown:
      return CompletionAction::None;
    default:
      return CompletionAction::Unknown;
    }
  case kontrol::mode::unknown:
  default:
    return CompletionAction::Unknown;
  }
}

auto completion_action_from_snapshot(kontrol::SystemSnapshot const& snapshot) -> CompletionAction {
  switch (snapshot.pending_action) {
  case kontrol::pending_action::nothing:
    return CompletionAction::None;
  case kontrol::pending_action::logout:
    return CompletionAction::Logout;
  case kontrol::pending_action::reboot:
    return CompletionAction::Reboot;
  case kontrol::pending_action::switch_to_integrated:
  case kontrol::pending_action::asus_egpu_disable:
    return CompletionAction::Unknown;
  default:
    break;
  }

  auto const pending_mode = normalize_mode(snapshot.pending_mode);
  auto const current_mode = normalize_mode(snapshot.current_mode);
  if (pending_mode != kontrol::mode::unknown && pending_mode != current_mode) {
    return completion_action_from_transition(current_mode, pending_mode);
  }

  return CompletionAction::Unknown;
}

auto completion_message(CompletionAction action, std::uint32_t requested_mode) -> QString {
  auto const target = mode_name_qt(requested_mode);

  switch (action) {
  case CompletionAction::None:
    return QStringLiteral("已提交切换到 %1，当前无需重启或注销。").arg(target);
  case CompletionAction::Logout:
    return QStringLiteral("已提交切换到 %1，需要注销才能完成切换。").arg(target);
  case CompletionAction::Reboot:
    return QStringLiteral("已提交切换到 %1，需要重启才能完成切换。").arg(target);
  case CompletionAction::Unknown:
  default:
    return QStringLiteral("已提交切换到 %1，请根据系统提示完成后续操作。").arg(target);
  }
}

auto apply_success_snapshot(kontrol::AppController& controller, kontrol::SystemSnapshot next_snapshot) -> void {
  controller.snapshot_data = std::move(next_snapshot);
  emit controller.snapshotChanged();
  emit controller.modesChanged();
}

auto set_action_bar(
  kontrol::AppController& controller,
  QString message,
  bool primary_visible,
  QString primary_text,
  kontrol::AppController::BarAction primary_action,
  bool secondary_visible = false,
  QString secondary_text = {},
  kontrol::AppController::BarAction secondary_action = kontrol::AppController::BarAction::None) -> void {
  controller.bar_visible = !message.trimmed().isEmpty();
  controller.status = std::move(message);
  controller.primary_visible = primary_visible;
  controller.primary_text = std::move(primary_text);
  controller.primary_action = primary_action;
  controller.secondary_visible = secondary_visible;
  controller.secondary_text = std::move(secondary_text);
  controller.secondary_action = secondary_action;

  emit controller.statusMessageChanged();
  emit controller.actionBarChanged();
}

auto apply_error(kontrol::AppController& controller, kontrol::GfxError const& error) -> void {
  auto const message = QString::fromStdString(error.message + " | " + error.remediation);
  set_action_bar(
    controller,
    message,
    false,
    {},
    kontrol::AppController::BarAction::None,
    true,
    QStringLiteral("关闭"),
    kontrol::AppController::BarAction::Dismiss);
}

auto start_detached(QString const& program, QStringList const& args) -> bool {
  return QProcess::startDetached(program, args);
}

auto request_logout() -> bool {
  if (start_detached(
        QStringLiteral("qdbus6"),
        {QStringLiteral("org.kde.Shutdown"), QStringLiteral("/Shutdown"), QStringLiteral("org.kde.Shutdown.logout")})) {
    return true;
  }

  if (start_detached(
        QStringLiteral("qdbus"),
        {QStringLiteral("org.kde.Shutdown"), QStringLiteral("/Shutdown"), QStringLiteral("org.kde.Shutdown.logout")})) {
    return true;
  }

  auto const session_id = qEnvironmentVariable("XDG_SESSION_ID");
  if (!session_id.isEmpty()) {
    return start_detached(QStringLiteral("loginctl"), {QStringLiteral("terminate-session"), session_id});
  }

  return false;
}

} // namespace

namespace kontrol {

AppController::AppController(QObject* parent)
  : QObject(parent)
  , backend(make_backend()) {
  refresh();
}

void AppController::refresh() {
  auto result = snapshot(backend);

  if (!result && std::holds_alternative<DbusBackend>(backend)) {
    auto fallback = CliBackend {};
    auto& primary = std::get<DbusBackend>(backend);
    result = run_with_fallback(primary, fallback, [](auto& selected) -> SnapshotResult {
      return selected.snapshot();
    });

    if (result) {
      backend = BackendVariant {fallback};
    }
  }

  if (!result) {
    apply_error(*this, result.error());
    return;
  }

  apply_success_snapshot(*this, *result);
}

void AppController::applyMode(quint32 raw_mode) {
  auto result = switch_mode(backend, raw_mode);
  if (!result && std::holds_alternative<DbusBackend>(backend)) {
    auto fallback = CliBackend {};
    auto fallback_result = fallback.switch_mode(raw_mode);
    if (fallback_result) {
      backend = BackendVariant {fallback};
      result = std::move(fallback_result);
    }
  }

  if (!result) {
    apply_error(*this, result.error());
    return;
  }

  apply_success_snapshot(*this, *result);
  has_requested_mode = false;
  requested_mode = 0U;

  auto const action = completion_action_from_snapshot(snapshot_data);
  if (action == CompletionAction::Logout) {
    set_action_bar(
      *this,
      completion_message(action, raw_mode),
      true,
      QStringLiteral("立即注销"),
      BarAction::LogoutNow,
      true,
      QStringLiteral("稍后处理"),
      BarAction::Dismiss);
    return;
  }

  if (action == CompletionAction::Reboot) {
    set_action_bar(
      *this,
      completion_message(action, raw_mode),
      true,
      QStringLiteral("立即重启"),
      BarAction::RebootNow,
      true,
      QStringLiteral("稍后处理"),
      BarAction::Dismiss);
    return;
  }

  if (action == CompletionAction::None) {
    set_action_bar(
      *this,
      completion_message(action, raw_mode),
      false,
      {},
      BarAction::None,
      true,
      QStringLiteral("关闭"),
      BarAction::Dismiss);
    return;
  }

  set_action_bar(
    *this,
    completion_message(CompletionAction::Unknown, raw_mode),
    false,
    {},
    BarAction::None,
    true,
    QStringLiteral("关闭"),
    BarAction::Dismiss);
}

void AppController::selectMode(quint32 raw_mode) {
  auto const current_mode = normalize_mode(snapshot_data.current_mode);
  auto const target_mode = normalize_mode(raw_mode);

  if (has_requested_mode && requested_mode == target_mode) {
    has_requested_mode = false;
    requested_mode = 0U;
    set_action_bar(*this, {}, false, {}, BarAction::None);
    return;
  }

  if (current_mode == target_mode) {
    has_requested_mode = false;
    requested_mode = 0U;
    set_action_bar(*this, {}, false, {}, BarAction::None);
    return;
  }

  has_requested_mode = true;
  requested_mode = target_mode;

  auto const message = mode_switch_hint(current_mode, target_mode);

  set_action_bar(
    *this,
    message,
    true,
    QStringLiteral("确认切换"),
    BarAction::ConfirmSwitch,
    true,
    QStringLiteral("取消"),
    BarAction::Dismiss);
}

void AppController::handlePrimaryAction() {
  switch (primary_action) {
  case BarAction::ConfirmSwitch:
    if (has_requested_mode) {
      applyMode(requested_mode);
    }
    return;
  case BarAction::RebootNow:
    if (start_detached(QStringLiteral("systemctl"), {QStringLiteral("reboot")})) {
      set_action_bar(*this, QStringLiteral("已发起重启请求。"), false, {}, BarAction::None);
    } else {
      set_action_bar(
        *this,
        QStringLiteral("发起重启失败，请手动执行 systemctl reboot。"),
        false,
        {},
        BarAction::None,
        true,
        QStringLiteral("关闭"),
        BarAction::Dismiss);
    }
    return;
  case BarAction::LogoutNow:
    if (request_logout()) {
      set_action_bar(*this, QStringLiteral("已发起注销请求。"), false, {}, BarAction::None);
    } else {
      set_action_bar(
        *this,
        QStringLiteral("发起注销失败，请手动注销会话。"),
        false,
        {},
        BarAction::None,
        true,
        QStringLiteral("关闭"),
        BarAction::Dismiss);
    }
    return;
  case BarAction::Dismiss:
  case BarAction::None:
  default:
    return;
  }
}

void AppController::handleSecondaryAction() {
  switch (secondary_action) {
  case BarAction::Dismiss:
    has_requested_mode = false;
    requested_mode = 0U;
    set_action_bar(*this, QStringLiteral(""), false, {}, BarAction::None);
    return;
  default:
    return;
  }
}

auto AppController::product_family() const -> QString {
  return QString::fromStdString(snapshot_data.product_family.empty() ? "未知" : snapshot_data.product_family);
}

auto AppController::board_name() const -> QString {
  return QString::fromStdString(snapshot_data.board_name.empty() ? "未知" : snapshot_data.board_name);
}

auto AppController::dgpu_vendor() const -> QString {
  return QString::fromStdString(snapshot_data.dgpu_vendor.empty() ? "未知" : snapshot_data.dgpu_vendor);
}

auto AppController::current_mode_label() const -> QString {
  return mode_name_qt(snapshot_data.current_mode);
}

auto AppController::pending_action_label() const -> QString {
  return kontrol::pending_action_label(snapshot_data.pending_action);
}

auto AppController::power_status_label() const -> QString {
  return kontrol::power_status_label(snapshot_data.power_status);
}

auto AppController::modes() const -> QVariantList {
  auto const preferred = std::array {
    kontrol::mode::asus_mux_dgpu,
    kontrol::mode::hybrid,
    kontrol::mode::integrated,
  };

  auto ordered = QVariantList {};
  ordered.reserve(static_cast<qsizetype>(preferred.size()));

  for (auto const raw_mode : preferred) {
    auto const found = std::ranges::find_if(snapshot_data.supported_modes, [&](auto const& mode) -> bool {
      return normalize_mode(mode.raw_mode) == raw_mode;
    });

    if (found != snapshot_data.supported_modes.end()) {
      ordered.push_back(to_variant(*found));
      continue;
    }

    ordered.push_back(to_variant(mode_to_option(raw_mode, true)));
  }

  return ordered;
}

auto AppController::action_bar_visible() const -> bool {
  return bar_visible;
}

auto AppController::status_message() const -> QString {
  return status;
}

auto AppController::action_primary_visible() const -> bool {
  return primary_visible;
}

auto AppController::action_primary_text() const -> QString {
  return primary_text;
}

auto AppController::action_secondary_visible() const -> bool {
  return secondary_visible;
}

auto AppController::action_secondary_text() const -> QString {
  return secondary_text;
}

auto AppController::last_snapshot() const -> SystemSnapshot {
  return snapshot_data;
}

} // namespace kontrol
