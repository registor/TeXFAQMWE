# LaTeXFAQMWE

[![Travis build](https://travis-ci.org/ustctug/ustcthesis.svg?branch=master)](https://travis-ci.org/ustctug/ustcthesis)
[![Github downloads](https://img.shields.io/github/downloads/ustctug/ustcthesis/total.svg)](https://github.com/ustctug/ustcthesis/releases)
[![GitHub release](https://img.shields.io/github/release/ustctug/ustcthesis/all.svg)](https://github.com/ustctug/ustcthesis/releases/latest)
[![GitHub commits](https://img.shields.io/github/commits-since/ustctug/ustcthesis/latest.svg)](https://github.com/ustctug/ustcthesis/commits/master)

这是一个用于记录在平时工作、交流中，与同事、网友问答过程中形成的LaTeX最小工作示例代码的项目，主要用于备份自己的工作。

Happy LaTeXing！~

注意：

1. 本文档要求 TeXLive、MacTeX、MikTeX 不低于 2018 年的发行版，并且尽可能升级到最新。

## 编译文档

- 编译各最小工作示例中的 `main.pdf`：
1. 支持minted代码排版宏包
   ```
   latexmk -xelatex -shell-escape main.tex
   ```
2. 不支持minted代码排版宏包
   ```
   latexmk -xelatex main.tex
   ```
3. 在与`main.tex` 同级目录下存在`.latexmkrc` 脚本文件的情况下，执行：
   ```
   latexmk
   ```
- 如需清理论文编译过程中的临时文件，可以：
   ```
   latexmk -c
   ```

## 反馈问题

如果发现代码有问题，请按照以下步骤操作：

1. 将 TeX 发行版和宏包升级到最新，并且将模板升级到 Github 上最新版本，
查看问题是否已经修复；
2. 在 [GitHub Issues](https://github.com/registor/csv2latextab/issues)
中搜索该问题的关键词；
3. 在 [GitHub Issues](https://github.com/registor/csv2latextab/issues)
中提出新 issue，并回答以下问题：
    - 使用了什么版本的 TeX Live / MacTeX / MikTeX ？
    - 具体的问题是什么？
    - 正确的结果应该是什么样的？
    - 是否应该附上相关源码或者截图？
4. 联系作者：西北农林科技大学信息工程学院耿楠
