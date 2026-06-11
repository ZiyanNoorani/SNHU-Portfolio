# SNHU Portfolio — Term 2026 C-3 (May–Jun 2026)

Coursework completed during the 8-week term at Southern New Hampshire University.

---

## CS-210: Programming Languages (C++)

### Project 1 — Chada Tech Dual Clock
A C++ console application displaying time simultaneously in 12-hour and 24-hour formats with user controls to add hours, minutes, or seconds.

### Project 2 — Airgead Banking Investment App
Object-oriented C++ application that calculates compound interest growth over time, both with and without monthly deposits. Follows the Airgead Banking Standards (OOP, `m_` prefix, `try/catch` error handling).

### Project 3 — Corner Grocer Item Tracker *(selected portfolio artifact)*
C++ program that reads a grocery purchase log, tallies item frequencies using `std::map`, and presents results as a list, histogram, or single-item lookup. Writes a `frequency.dat` backup automatically.

### CS-210 Reflection

The Corner Grocer project solved a real inventory problem: a grocery store needed a fast way to see how often each item was purchased throughout the day. The program reads a plain-text purchase log, tallies every item using a `std::map`, and gives the user four options — look up a single item, print all frequencies, display a histogram, or exit. A `frequency.dat` backup is written automatically at startup so the data is never lost between sessions.

What I did particularly well was input validation and error handling. Every menu interaction is guarded against non-numeric input and out-of-range choices, so the program never crashes on bad user input. I also kept the class interface clean — `GroceryTracker` owns all the file I/O and data logic, and `main.cpp` is purely a driver, which made the code easy to read and test in pieces.

There are a few places I could improve the code. The histogram currently prints one asterisk per purchase, which breaks down visually for high-frequency items; a scaled version that caps at a fixed width would be more readable. Adding file-not-found error messaging and support for case-insensitive lookups without normalizing to lowercase at load time would also make the program more robust. If I were expanding this for production use, I would replace the flat text file with a small SQLite database to support filtering and date-range queries.

The most challenging part was getting the input file to load correctly in Visual Studio, since the working directory at runtime is not the project root by default. I resolved it by placing the `.txt` file alongside the `.vcxproj` file and verifying the path with a debug print. That experience taught me to always confirm file paths at runtime rather than assuming them, which is a habit I will carry into every future project. The `std::map` and file stream patterns I practiced here are directly transferable to any data-processing work in C++ or similar languages, and the class-separation discipline applies to every OOP project regardless of language.

---

## CS-250: Software Development Lifecycle (Agile/Scrum)

### Final Project — SNHU Travel Sprint Review & Retrospective *(selected portfolio artifact)*
3–4 page APA-formatted document reflecting on the full SNHU Travel project arc, covering Scrum roles, user story completion, handling mid-sprint change (wellness pivot), communication, and evaluation of the Agile process.

### Final Project — SNHU Travel Agile Presentation
5-slide presentation summarizing the Scrum-Agile methodology as applied to the SNHU Travel project, with academic and professional sources.

### CS-250 Reflection

Interpreting user needs starts with talking to the people who have them. In the SNHU Travel project, acting as Product Owner meant interviewing stakeholders to surface priorities that were easy to overlook from a purely technical perspective — things like mobile usability and transparent cancellation policies. User stories gave those needs a structured form: "As a [user], I want [feature], so that [benefit]" keeps the team focused on outcomes rather than implementation details, and pairing each story with acceptance criteria creates a shared, testable definition of done. That combination — a story that names the goal and criteria that define completion — is what let us catch the ambiguous "quickly" in a booking-confirmation story before it became a defect.

My approach to development has shifted toward iteration. Rather than trying to anticipate every requirement up front, I now think in terms of short cycles: plan a small increment, build it, get feedback, and adjust. The SNHU Travel project made that concrete when a mid-sprint pivot to wellness destinations arrived. Because the architecture had been built around well-scoped, stable stories, absorbing the change meant swapping content rather than rewriting structure. Going forward I want to keep that discipline — writing stories small enough to finish in a sprint, holding retrospectives even on solo projects, and treating a backlog as a living document rather than a fixed spec.

Being a good team member in software development means making your work visible and your blockers audible. The Daily Scrum format — what I did, what I am doing, what is in the way — is useful not because it is a status report but because naming a blocker out loud is what gets it resolved. In the SNHU Travel project, flagging the ambiguous confirmation-timing question to the Product Owner before writing test cases prevented a defect and saved rework. Good teammates also do not wait to be asked; they surface problems early, review each other's work honestly, and respect that every role — Product Owner, developer, tester, Scrum Master — depends on the others doing theirs well.

---

## DAD-220: Introduction to Structured Database Environments (SQL/MySQL)

### Project 1 — QuantigrationUpdates Database
Built a MySQL relational database (`QuantigrationUpdates`) with Customers, Orders, and RMA tables. Ran queries, performed DML operations, renamed tables/columns, and exported data to CSV.

### Project 2 — Quantigration RMA Analysis
Analyzed return merchandise authorization data using SQL: counted returns by U.S. state and calculated percentage of returns by product type.

---

*Southern New Hampshire University | Bachelor of Science in Computer Science*

---

*AI usage acknowledgment: Anthropic's Claude was used to assist with organizing and drafting the reflection responses in this README.*
