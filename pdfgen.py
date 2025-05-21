#!/usr/bin/env python3
import os
import subprocess
import sys

def escape_latex(s):
    return s.replace('_', r'\_')

REPO_URL = "https://github.com/rafaelGuasselli/structures.git"
REPO_DIR = "./"
TEX_FILE = "structures_all.tex"

# 2. Identify topic directories (skip 'tests' and any files at root)
topics = []
for entry in os.listdir(REPO_DIR):
    path = os.path.join(REPO_DIR, entry)
    if entry == "tests" or entry == ".git" or entry == ".vscode" or not os.path.isdir(path):
        continue
    topics.append(entry)
topics.sort()

# 3. Begin writing LaTeX file
with open(TEX_FILE, 'w') as tex:
    tex.write(r"""\documentclass[11pt,landscape,twocolumn]{article}
\usepackage[margin=1.5cm,landscape]{geometry}
\usepackage{listings}
\usepackage{lmodern}
\usepackage[T1]{fontenc}
\usepackage{tocloft}
\usepackage[utf8]{inputenc}
\usepackage{textcomp}
\usepackage[portuguese]{babel}
\usepackage{upquote}  % Fix quotes in listings
\usepackage{xcolor}   % For colored text

% Listings configuration with improved character handling
\lstset{
  inputencoding=utf8,
  extendedchars=true,
  basicstyle=\ttfamily\small,
  breaklines=true,
  breakatwhitespace=false,
  columns=fullflexible,
  keepspaces=true,
  showstringspaces=false,
  frame=single,
  literate=
    {á}{{\'a}}1 {é}{{\'e}}1 {í}{{\'i}}1 {ó}{{\'o}}1 {ú}{{\'u}}1
    {Á}{{\'A}}1 {É}{{\'E}}1 {Í}{{\'I}}1 {Ó}{{\'O}}1 {Ú}{{\'U}}1
    {à}{{\`a}}1 {è}{{\`e}}1 {ì}{{\`i}}1 {ò}{{\`o}}1 {ù}{{\`u}}1
    {À}{{\`A}}1 {È}{{\`E}}1 {Ì}{{\`I}}1 {Ò}{{\`O}}1 {Ù}{{\`U}}1
    {ä}{{\"a}}1 {ë}{{\"e}}1 {ï}{{\"i}}1 {ö}{{\"o}}1 {ü}{{\"u}}1
    {Ä}{{\"A}}1 {Ë}{{\"E}}1 {Ï}{{\"I}}1 {Ö}{{\"O}}1 {Ü}{{\"U}}1
    {â}{{\^a}}1 {ê}{{\^e}}1 {î}{{\^i}}1 {ô}{{\^o}}1 {û}{{\^u}}1
    {Â}{{\^A}}1 {Ê}{{\^E}}1 {Î}{{\^I}}1 {Ô}{{\^O}}1 {Û}{{\^U}}1
    {ã}{{\~a}}1 {ñ}{{\~n}}1 {õ}{{\~o}}1
    {Ã}{{\~A}}1 {Ñ}{{\~N}}1 {Õ}{{\~O}}1
    {ç}{{\c c}}1 {Ç}{{\c C}}1
    {°}{{\textdegree}}1
}

\title{Competitive Programming Team Book}
\author{}
\date{\today}

\begin{document}
\maketitle
\tableofcontents
\newpage
""")

    for topic in topics:
        tex.write(f"\\section{{{topic}}}\n")
        topic_dir = os.path.join(REPO_DIR, topic)
        files = sorted([f for f in os.listdir(topic_dir) 
                        if os.path.isfile(os.path.join(topic_dir,f)) and
                           os.path.splitext(f)[1] in ['.cpp', '.h', '.hpp']])
        for fname in files:
            tex.write(f"\\subsection*{{{escape_latex(fname)}}}\n")
            tex.write("\\begin{lstlisting}\n")
            try:
                # Try UTF-8 encoding first
                with open(os.path.join(topic_dir, fname), 'r', encoding='utf-8') as f:
                    tex.write(f.read())
            except UnicodeDecodeError:
                # If UTF-8 fails, try latin-1 (ISO-8859-1) which is more forgiving
                try:
                    with open(os.path.join(topic_dir, fname), 'r', encoding='latin-1') as f:
                        tex.write(f.read())
                except Exception as e:
                    print(f"Warning: Could not read file {fname} properly: {e}")
                    tex.write(f"// Error reading file: {fname}")
            tex.write("\n\\end{lstlisting}\n\n")

    tex.write("\\end{document}")


# 5. Compile LaTeX to PDF (twice for TOC correctness)
print("Compiling LaTeX to PDF...")
success = True
for i in range(2):
    try:
        print(f"Running pdflatex iteration {i+1}...")
        # Run with shell=True to see the output
        ret = subprocess.run(["pdflatex", "-interaction=nonstopmode", TEX_FILE], shell=False)
        print(f"Return code: {ret.returncode}")
        
        # Important change: Many LaTeX errors are not fatal for PDF production
        # We should check if the PDF was actually created despite errors
        if ret.returncode != 0:
            print(f"pdflatex had errors on iteration {i+1} with return code {ret.returncode}", file=sys.stderr)
            print("Checking if PDF was produced anyway...")
        
        # Continue with next iteration even if there were errors
    except Exception as e:
        print(f"Error running pdflatex: {e}", file=sys.stderr)
        success = False
        break

# Check if the PDF file exists and has a reasonable size
pdf_file = TEX_FILE.replace(".tex", ".pdf")
if os.path.exists(pdf_file) and os.path.getsize(pdf_file) > 1000:  # More than 1KB
    print("PDF generated successfully despite possible LaTeX warnings/errors.")
    # Don't exit with error code even if there were non-fatal LaTeX errors
else:
    print("PDF generation failed or produced an empty file.", file=sys.stderr)
    sys.exit(1)

# 6. Remove auxiliary files except for the PDF
for ext in ['aux', 'log', 'out', 'toc']:
 fname = f"structures_all.{ext}"
 if os.path.exists(fname):
  os.remove(fname)