

import PyPDF2
import subprocess

def merge_pdf():
    pdfs = [
        subprocess.run(['wslpath','-u',
                        r"C:\Users\k\OneDrive\Desktop\1.pdf"
                        ] ,capture_output = True,text = True).stdout.strip(),
        subprocess.run(['wslpath', '-u',
                 r"C:\Users\k\OneDrive\Desktop\2.pdf"
                 ],capture_output = True, text = True).stdout.strip(),
    ]

    merger = PyPDF2.PdfMerger()
    for pdf in pdfs:
        merger.append(pdf)
    merger.write(    subprocess.run(['wslpath', '-u',
                    r"C:\Users\k\OneDrive\Desktop\xxxxx.pdf"
                    ], capture_output=True, text=True).stdout.strip())
    merger.close()


from pdf2docx import Converter

def pdftoword():
    ifs = r"D:\fold\🐎\2.pdf"
    ofs = r"D:\fold\🐎\2.docx"
    cv = Converter(ifs)
    cv.convert(ofs, start = 0, end = None)
    cv.close()
