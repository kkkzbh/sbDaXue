#pragma once

#include "core/gfx_dispatch.h"

#include <QtCore/QObject>
#include <QtCore/QVariantList>

#include <cstdint>

namespace kontrol {

struct AppController : QObject {
  Q_OBJECT
  Q_PROPERTY(QString productFamily READ product_family NOTIFY snapshotChanged)
  Q_PROPERTY(QString boardName READ board_name NOTIFY snapshotChanged)
  Q_PROPERTY(QString dgpuVendor READ dgpu_vendor NOTIFY snapshotChanged)
  Q_PROPERTY(QString currentModeLabel READ current_mode_label NOTIFY snapshotChanged)
  Q_PROPERTY(QString pendingActionLabel READ pending_action_label NOTIFY snapshotChanged)
  Q_PROPERTY(QString powerStatusLabel READ power_status_label NOTIFY snapshotChanged)
  Q_PROPERTY(QVariantList modes READ modes NOTIFY modesChanged)
  Q_PROPERTY(bool actionBarVisible READ action_bar_visible NOTIFY actionBarChanged)
  Q_PROPERTY(QString statusMessage READ status_message NOTIFY statusMessageChanged)
  Q_PROPERTY(bool actionPrimaryVisible READ action_primary_visible NOTIFY actionBarChanged)
  Q_PROPERTY(QString actionPrimaryText READ action_primary_text NOTIFY actionBarChanged)
  Q_PROPERTY(bool actionSecondaryVisible READ action_secondary_visible NOTIFY actionBarChanged)
  Q_PROPERTY(QString actionSecondaryText READ action_secondary_text NOTIFY actionBarChanged)

public:
  explicit AppController(QObject* parent = nullptr);

  Q_INVOKABLE void refresh();
  Q_INVOKABLE void applyMode(quint32 raw_mode);
  Q_INVOKABLE void selectMode(quint32 raw_mode);
  Q_INVOKABLE void handlePrimaryAction();
  Q_INVOKABLE void handleSecondaryAction();

  auto product_family() const -> QString;
  auto board_name() const -> QString;
  auto dgpu_vendor() const -> QString;
  auto current_mode_label() const -> QString;
  auto pending_action_label() const -> QString;
  auto power_status_label() const -> QString;
  auto modes() const -> QVariantList;

  auto action_bar_visible() const -> bool;
  auto status_message() const -> QString;
  auto action_primary_visible() const -> bool;
  auto action_primary_text() const -> QString;
  auto action_secondary_visible() const -> bool;
  auto action_secondary_text() const -> QString;

  auto last_snapshot() const -> SystemSnapshot;

  Q_SIGNAL void snapshotChanged();
  Q_SIGNAL void modesChanged();
  Q_SIGNAL void statusMessageChanged();
  Q_SIGNAL void actionBarChanged();

  enum struct BarAction : std::uint8_t {
    None,
    ConfirmSwitch,
    RebootNow,
    LogoutNow,
    Dismiss,
  };

  BackendVariant backend {};
  SystemSnapshot snapshot_data {};

  bool bar_visible = false;
  QString status {};
  bool primary_visible = false;
  QString primary_text {};
  BarAction primary_action = BarAction::None;
  bool secondary_visible = false;
  QString secondary_text {};
  BarAction secondary_action = BarAction::None;

  bool has_requested_mode = false;
  quint32 requested_mode = 0U;
};

} // namespace kontrol
