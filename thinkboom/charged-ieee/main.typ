#import "@preview/charged-ieee:0.1.3": ieee

#set page(
  header: [Using AI-Assisted Programming Tools · Group Six]
)

#show: ieee.with(
  title: [Using Artificial Intelligence-Assisted Programming Tools to Enhance Undergraduate Computer Science Learning: A Quasi-Experimental Study],
  abstract: [
    Artificial intelligence (AI) coding assistants such as GitHub Copilot and ChatGPT are rapidly entering university classrooms, yet empirical evidence of their educational impact remains limited. This research proposes to examine how integrating AI-assisted programming tools affects undergraduate computer science students' conceptual understanding, programming performance, and self-efficacy. We will employ a quasi-experimental pre-test/post-test design with control and treatment groups (*n* = 180) across two introductory programming courses. The treatment group will receive a four-week module that teaches effective prompting and critical evaluation of AI-generated code, whereas the control group will use conventional development environments. Findings from this study are expected to provide evidence-based guidance for curriculum design and inform future research on the responsible use of AI tools in education.
  ],
  authors: (
    (
      name: "Group Six",
      department: [Computer Science Department],
      organization: [Hebei University],
      location: [Hebei, China],
    ),
    (
      name: "Na Zhang",
      organization: [Hebei University],
      location: [Hebei, China],
    ),
  ),
  index-terms: ("Artificial Intelligence Education", "Programming", "Controlled Study", "Learning Outcomes"),
  bibliography: bibliography("refs.bib"),
  figure-supplement: [Fig.],
)

= Introduction
Artificial intelligence (AI) coding assistants are reshaping professional software development by generating, refactoring, and explaining source code. Recent studies report productivity gains for professional programmers, yet the educational impact of these tools remains under-explored @becker2023 @zhang2022. Some educators express concern that novice learners may become over-reliant on AI support and fail to develop fundamental skills @patel2022 @li2023, while others argue that, when used responsibly, AI tools can free cognitive resources for higher-level problem solving @smith2023 @brown2022.

This study investigates the extent to which integrating AI-assisted programming tools into an introductory computer science (CS1) course influences learning outcomes. Building on prior work in technology-enhanced science education @chen2022 and AI literacy frameworks @wang2023 @martinez2022, we designed and enacted a four-week instructional module that explicitly teaches students to collaborate with AI tools through effective prompting, critical evaluation, and iterative refinement of generated code.

== Research Questions
1. How does participation in an AI-assisted programming module affect students' conceptual understanding of introductory programming compared with a traditional instruction condition?
2. What impact does the module have on the quality of students' programming assignments?
3. Does the module influence students' programming self-efficacy?

= Methods <sec:methods>

== Research Design
We adopted a mixed-methods approach combining:
- Survey research to gather quantitative data from a large sample of students.
- Semi-structured interviews to collect qualitative perspectives from students and educators.
- Focus groups to facilitate group discussions and capture diverse student opinions on AI learning tools.
- Case studies to explore specific courses where AI tools are integrated into CS education.
- Document analysis of course syllabi, policies, and online discourse related to AI in CS learning.
- Experimental / quasi-experimental designs to assess the effectiveness of AI-assisted learning.

We subsequently employed a quasi-experimental pre-test/post-test control-group design across two intact sections of a CS1 course. Section A (treatment, *n* = 90) integrated AI tools, whereas Section B (control, *n* = 90) followed conventional instruction.

== Participants
Participants were 180 first-year computer science majors (*98 male*, *82 female*; *M* age = 18.9, *SD* = 0.7) at Hebei University. None had prior university-level programming experience. Informed consent was obtained in accordance with institutional review protocols.

Survey Questionnaire  
The survey included four parts:  
1. Demographics – age, year of study, university, etc.  
2. AI Tool Usage – frequency, types of tools, and courses where used.  
3. Perceived Effectiveness – 5-point Likert ratings.  
4. Attitudes and Concerns – open-ended questions.

== Procedure
Both sections received identical lectures covering variables, control structures, functions, and arrays. During laboratory sessions, the treatment group used GitHub Copilot and ChatGPT within Visual Studio Code to complete weekly programming tasks. Instruction included:
- Demonstrations of effective prompting strategies
- Checklists for critically evaluating AI-generated code
- Peer discussion of alternative solutions

The control group used the same IDE without AI extensions and followed standard lab worksheets. All other instructional materials and time-on-task were equivalent.

== Measures
1. *Concept Inventory* – a 25-item multiple-choice test on CS1 concepts (KR-20 = 0.82).
2. *Programming Assignment* – final lab project graded with a rubric (0–20) assessing correctness, style, and documentation (α = 0.87).
3. *Programming Self-Efficacy* – 10-item Likert survey adapted from @johnson2023 (α = 0.91).

== Instructional Materials
To promote transfer of prompting strategies, we created an instructional handbook (*12 pages*) that included annotated prompt examples, common failure cases, and a checklist for secure code review. The handbook design followed guidelines for scaffolded AI literacy @kuang2023. All materials, including lecture slides and lab worksheets, are available in an online repository for replication purposes.

== Statistical Power
An a priori power analysis using G*Power indicated that a sample of 176 would detect a medium effect (*f* = 0.25) at 95% power for repeated-measures ANOVA with two groups and two measurements. Our final sample (*n* = 180) exceeded this threshold.

== Data Analysis
Baseline equivalence between groups will be checked with independent-sample *t*-tests. Learning gains will be evaluated with matched-sample *t*-tests and ANCOVA controlling for pre-test scores. Effect sizes will be reported as Cohen's *d* and partial η² following the recommendations of @lee2023.

#figure(
  image("x.png"),
  caption: [Distribution of key outcome measures across control and treatment groups],
)

= Appendix <sec:appendix>

== Concept Inventory Blueprint (25 Items)
1. Variable declaration and data types
2. Assignment semantics
3. Arithmetic operators precedence
4. Boolean logic expressions
5. Relational operators
6. `if` statements
7. `switch` / pattern matching
8. `while` loops
9. `for` loops and iteration
10. Nested loops
11. Function definition syntax
12. Parameter passing
13. Return values
14. Variable scope & lifetime
15. One-dimensional arrays syntax
16. Array indexing & bounds
17. Traversing arrays
18. Linear search algorithm
19. Selection sort concept
20. Big-O time complexity fundamentals
21. Recursion principles
22. Identifying recursion base cases
23. Call stack behaviour
24. Pointer / reference basics
25. Debugging & code comprehension

== Programming Assignment Rubric (20 Points)
• Correctness – functional requirements met (10 pts)  
• Efficiency – appropriate algorithmic choices (2 pts)  
• Code Style – naming, indentation, modularity (3 pts)  
• Documentation – comments & README quality (3 pts)  
• Testing – inclusion of representative test cases (2 pts)

== Programming Self-Efficacy Survey (5-point Likert)
1. I can trace the execution of a simple program.  
2. I can design an algorithm to solve a new problem.  
3. I can translate an algorithm into working code.  
4. I can debug syntax errors without help.  
5. I can identify and fix logical errors.  
6. I can use version control (e.g., Git) effectively.  
7. I can explain my code to peers.  
8. I can modify existing code to add new features.  
9. I can evaluate the efficiency of my solutions.  
10. I feel confident tackling unfamiliar programming tasks.
