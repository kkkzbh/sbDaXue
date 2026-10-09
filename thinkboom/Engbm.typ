#import "@preview/touying:0.6.1": *
#import "@preview/pintorita:0.1.4": *
#import themes.metropolis: *
#import "@preview/numbly:0.1.0": numbly

#show: metropolis-theme.with(
  aspect-ratio: "16-9",
  footer: self => self.info.institution,
  config-info(
    title: [Using Artificial Intelligence-Assisted Programming Tools to Enhance Undergraduate Computer Science Learning],
    subtitle: [A Quasi-Experimental Study],
    author: [Gao Kangjia],
    date: datetime.today(),
    institution: [Hebei University],
    logo: emoji.robot,
  ),
)

#show raw.where(lang: "pintora"): it => pintorita.render(it.text)

#set heading(numbering: numbly("{1}.", default: "1.1"))

#title-slide()

= Outline <touying:hidden>

#outline(title: none, indent: 1em, depth: 1)

= Introduction

---

#slide[
  #set text(size: 23pt)
AI coding assistants such as GitHub Copilot and ChatGPT are rapidly entering university classrooms. *Yet empirical evidence of their educational impact remains limited*.

This study explores how integrating AI-assisted programming tools affects:
- Students' conceptual understanding
- Students' programming performance
- Students' programming self-efficacy
]

== Motivation

#slide[
  #set text(size: 20pt)
  - *Promise:* AI assistants are a proven productivity multiplier in industry. Can we adapt this power for student learning?
  - *Peril:* Without guidance, students risk becoming dependent on AI, potentially hindering the development of fundamental skills.
  - *Path Forward:* Explicit instruction in critical AI collaboration can transform these tools from a simple crutch into a powerful cognitive scaffold.
  - *Imperative:* This educational shift requires a strong evidence base. Our study is designed to provide it.
]

= Research Questions

---

#slide[
  #set text(size: 24pt)
  Our research seeks to answer three core questions:
  + *Knowledge:* Does AI assistance improve students' conceptual understanding of programming?
  + *Performance:* Does it enhance the quality of their practical coding assignments?
  + *Confidence:* Does it positively influence their programming self-efficacy?
]

= Methods

== Experimental Design

#slide[
  #align(center)[
    #image("experimental_design_flowchart.svg", width: 65%)
  ]
]

== Measures & Outcomes

#slide[
  #set text(size: 22pt)
  We assess impact across three domains using validated instruments:
  - *Conceptual Knowledge:* A 25-item CS1 concept inventory (KR-20 = 0.82).
  - *Programming Performance:* A final project graded via a detailed rubric (α = 0.87).
  - *Self-Efficacy:* A 10-item Likert survey on programming confidence (α = 0.91).
]

== Data Analysis Plan

#slide[
  #set text(size: 22pt)
  - *Power:* A priori analysis confirms our sample (_n_=180) is sufficient to detect a medium effect (*f*=0.25) with >95% power.
  - *Baseline:* Independent _t_-tests will check for pre-existing group differences.
  - *Gains:* Matched-sample _t_-tests and ANCOVA (controlling for pre-test scores) will evaluate learning gains.
  - *Effect Size:* We will report Cohen's _d_ and partial η² to quantify the magnitude of effects.
]

= Expected Contributions

#slide[
  #set text(size: 24pt)
  We anticipate our findings will make three key contributions:
  - *For Researchers:* Establishing a rigorous empirical benchmark on the impact of AI tools in introductory programming education.
  - *For Educators:* Providing evidence-based guidelines for the responsible integration of AI into the CS curriculum.
  - *For the Community:* Supplying a full suite of open educational resources (OER) to support replication and extension studies.
]


#focus-slide[
  #set align(center)
  #text(size: 32pt)[Thank You]
  
//   \
//   \
//   *Contact: `group.six@example.com`* \
//   *Resources: `github.com/example/ai-cs1-study`*
]
