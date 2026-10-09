"""Build the music coursework site with only the assets it references."""

from html.parser import HTMLParser
from pathlib import Path
import re
import shutil
from urllib.parse import unquote, urlsplit


ROOT = Path(__file__).resolve().parent
OUTPUT = ROOT / "dist"
MAX_ASSET_BYTES = 25 * 1024 * 1024


class AssetReferences(HTMLParser):
    def __init__(self):
        super().__init__()
        self.references = set()

    def handle_starttag(self, tag, attrs):
        for name, value in attrs:
            if value and name in {"src", "href", "data-src"}:
                self.references.add(value)


html = (ROOT / "QQmusic.html").read_text(encoding="utf-8")
parser = AssetReferences()
parser.feed(html)
pending = list(parser.references)
pending.extend(re.findall(r"url\(\s*['\"]?([^)'\"]+)", html))
assets = set()
while pending:
    reference = urlsplit(pending.pop())
    if reference.scheme or reference.netloc or not reference.path:
        continue
    asset = (ROOT / unquote(reference.path)).resolve()
    asset.relative_to(ROOT)
    if asset in assets:
        continue
    if not asset.is_file():
        raise FileNotFoundError(f"Referenced asset is missing: {asset}")
    if asset.stat().st_size > MAX_ASSET_BYTES:
        raise ValueError(f"Asset exceeds the Cloudflare Pages 25 MiB limit: {asset}")
    assets.add(asset)
    if asset.suffix == ".css":
        pending.extend(re.findall(r"url\(\s*['\"]?([^)'\"]+)", asset.read_text(encoding="utf-8")))

if OUTPUT.exists():
    shutil.rmtree(OUTPUT)
OUTPUT.mkdir()
(OUTPUT / "index.html").write_text(html, encoding="utf-8")
for asset in sorted(assets):
    destination = OUTPUT / asset.relative_to(ROOT)
    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(asset, destination)
print(f"Built {len(assets) + 1} files in {OUTPUT}")
