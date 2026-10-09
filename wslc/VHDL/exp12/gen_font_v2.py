from PIL import Image, ImageDraw, ImageFont
import math

text = "哈哈哈"
# Try to find a font that supports Chinese
font_paths = [
    "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc",
    "/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc",
    "/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf",
    "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
]

font = None
for path in font_paths:
    try:
        font = ImageFont.truetype(path, 12)
        print(f"Loaded font: {path}")
        break
    except Exception as e:
        continue

if font is None:
    print("Error: No suitable font found.")
    exit(1)

char_width = 16
char_height = 16

print(f"-- Generated for text: {text}")
print(f"CONSTANT CHAR_NUM : INTEGER := {len(text)};")
print("CONSTANT font_data : char_rom := (")

for i, char in enumerate(text):
    # Create image for character
    img = Image.new('1', (char_width, char_height), 0)
    draw = ImageDraw.Draw(img)
    
    # Get bounding box to center
    try:
        bbox = draw.textbbox((0, 0), char, font=font)
        w = bbox[2] - bbox[0]
        h = bbox[3] - bbox[1]
    except AttributeError:
        # Fallback for older Pillow versions
        w, h = draw.textsize(char, font=font)
        bbox = [0, 0, w, h]
    
    x = (char_width - w) // 2
    y = (char_height - h) // 2
    # Adjust y slightly up
    y -= 2
    
    draw.text((x, y), char, font=font, fill=1)
    
    # Mirror the image left-to-right
    img = img.transpose(Image.FLIP_LEFT_RIGHT)
    
    print(f"    -- {i}: {char} (Mirrored)")
    print("    (", end="")
    
    rows_hex = []
    for r in range(char_height):
        row_val = 0
        for c in range(char_width):
            pixel = img.getpixel((c, r))
            if pixel:
                row_val |= (1 << (15 - c)) # MSB is column 0? 
                # VHDL: std_logic_vector(15 downto 0)
                # Usually index 15 is MSB.
                # If we want col 0 to be MSB, then 1<<(15-c).
                # If we want col 0 to be LSB, then 1<<c.
                # The previous code used X"..." which maps to 15 downto 0.
                # Let's assume 15 is left-most pixel.
        
        rows_hex.append(f'X"{row_val:04X}"')
    
    print(", ".join(rows_hex), end="")
    
    if i < len(text) - 1:
        print("),")
    else:
        print(")")

print(");")
