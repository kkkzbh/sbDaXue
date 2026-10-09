// 这是一个Typst报告模板。
//
// 如何使用:
// 1. 在你的主typst文件中导入此模板:
//    #import "report_template.typ": report
//
// 2. 用你的内容调用`report`函数:
//    #show: report(
//      header-text: "我的实验报告",
//      show-abstract: true,
//      abstract: [
//        这是报告的摘要。它描述了工作的主要发现和贡献。
//      ],
//      show-toc: true,
//    )
//
//    = 引言
//    这是报告的第一部分。
//
//    == 背景
//    这里是一些背景信息。

#let report(
  header-text: "实验报告",
  show-abstract: true,
  abstract: none,
  show-toc: true,
  body
) = {
  // 1. 设置文档样式
  // ==========================

  // 设置页面属性
  set page(
    paper: "a4",
    margin: (top: 2.5cm, bottom: 2.5cm, left: 2.5cm, right: 2.5cm),
    header: [
      #set text(size: 10pt)
      #grid(
        columns: (1fr, 1fr),
        align: (left, right),
        [#header-text],
        [网络空间安全与计算机学院] // 这部分来自原始文件，可以自定义。
      )
      #line(length: 100%, stroke: 0.5pt)
    ]
  )

  // 设置文本属性
  set text(
    font: ("New Computer Modern"),
    size: 12pt,
    lang: "zh"
  )

  // 设置段落属性
  set par(justify: true, leading: 0.65em)

  // 设置标题样式
  set heading(numbering: "1.1.1")

  show heading.where(level: 1): it => {
    if counter(heading).at(it.location()).first() > 1 {
      pagebreak()
    }
    align(center)[
      #set text(size: 16pt, weight: "bold")
      #v(0.5em)
      #it
      #v(0.3em)
    ]
  }

  show heading.where(level: 2): it => {
    v(0.4em)
    h(1em)
    set text(size: 14pt, weight: "bold")
    it
    v(0.2em)
  }

  show heading.where(level: 3): it => {
    v(0.3em)
    h(2em)
    set text(size: 12pt, weight: "bold")
    it
    v(0.1em)
  }

  // 设置图表样式
  // 1. Disable all automatic numbering for figures.
  set figure(numbering: none, supplement: [])

  // 2. Create our own counters.
  let fig-counter = counter("fig")
  let tbl-counter = counter("tbl")
  
  // 初始化计数器从1开始
  fig-counter.update(1)
  tbl-counter.update(1)

  // 3. Show rule to implement everything manually.
  show figure: it => {
    context {
      let elem = if it.kind == table {
        tbl-counter.step()
        [表 #tbl-counter.display() #h(1em) #it.caption]
      } else {
        fig-counter.step()
        [图 #fig-counter.display() #h(1em) #it.caption]
      }

      v(0.5em, weak: true)
      align(center, {
        it.body
        if it.caption != none {
          v(0.5em, weak: true)
          text(size: 11pt, elem)
        }
      })
      v(1em, weak: true)
    }
  }

  // 2. 文档正文
  // =================

  // 摘要页
  if show-abstract and abstract != none {
    align(center)[
      #text(size: 18pt, weight: "bold")[摘 要]
    ]
    v(1em)
    abstract
    pagebreak()
  }

  // 目录页
  if show-toc {
    align(center)[
      #text(size: 18pt, weight: "bold")[目录]
    ]
    v(1em)
    outline(
      title: none,
      depth: 3,
      indent: auto
    )
    pagebreak()
  }

  // 主要内容
  // 主要内容页码从1开始。
  counter(page).update(1)
  set page(footer: align(center)[#context counter(page).display()])

  body
} 