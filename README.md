# SNHU Portfolio

Coursework completed at Southern New Hampshire University, organized by term.

---

# Term 2026 C-5 (Aug–Oct 2026)

## CS-330: Computational Graphics and Visualization (OpenGL/C++)

Files: [`CS-330/`](./CS-330)

### Final Project: 3D Desk Scene *(selected portfolio artifact)*
OpenGL and C++ scene that recreates my own desk from reference photos I took: a monitor on a riser, a mechanical keyboard, a HyperX QuadCast microphone on its stand, a mouse, and a folding phone stand holding a phone. Every object is built from primitive meshes, textured, and lit with the Phong model. The camera moves with WASD, rises and drops with Q and E, looks around with the mouse, changes speed with the scroll wheel, and switches between perspective and orthographic views with P and O. The ZIP holds the full Visual Studio solution and the texture images.

### Design Decisions Document
Explains why each object was built from the shapes it uses, how the camera and input controls work, how lighting and textures were chosen, and how the code is organized for reuse.

### CS-330 Reflection

**How do I approach designing software?**

This project taught me to decompose. A microphone on a stand is a cylinder for the body, a smaller cylinder for the neck, and a flat cylinder for the base. A monitor is a thin box for the screen, a slightly larger box behind it for the bezel, and a wider box under it for the riser. Once every object was reduced to primitives, the hard question became proportion, so I picked one object as the unit of measure and sized everything else against it, checking the result against the photo instead of trusting my memory of the desk. My process ran in a fixed order: reference photo, a sketch of each object as shapes, position and scale values written down as named constants, and only then code. Instructor feedback shaped the design along the way. In Module Two my pyramids rendered at full depth and did not match a flat 2D reference, which taught me that matching the reference beats making something look impressive. At Milestone Two the instructor praised the use of constants and functions and asked for one class per object, which pushed the scene toward code where adding a new object does not mean editing a 500-line function. The tactic I will carry forward is the same one in any system design: break the problem into parts small enough to name, define how big each part is relative to the others, and write that plan down before writing code.

**How do I approach developing programs?**

I built the scene one layer per milestone: basic shapes first, then the camera, then textures, then lighting. Inside each layer I added one object or one feature at a time and compiled and ran after every change, because a black screen after ten edits tells you nothing, while a black screen after one edit tells you exactly where to look. Order of transformations was the bug I hit most. Scale, then rotate, then translate gives a different result from any other order, and an object that flies off-screen is almost always a sign the order is wrong. Iteration also meant going back. I added mouse-look and a narrower field of view to the camera during Module Three, ahead of schedule, then tuned the movement speed later once the full scene showed it felt too fast. The toolchain gave me a lesson too. My machine runs Visual Studio 2026, while the course projects pin the v143 platform toolset from Visual Studio 2022, which threw MSB8020 errors until I resolved the toolset mismatch. Over the milestones my code moved from long blocks of copied draw calls, to reusable functions with named constants, to a structure organized around the objects themselves. Each step made the next milestone faster to finish.

**How can computer science help me in reaching my goals?**

My long-term goal is data analytics and data engineering, and graphics is the layer under every chart I will build. Model, view, and projection matrices are the same math that maps a data value to a pixel on a plot, and working with them directly in this course gave me a practical feel for linear algebra that will carry into statistics and machine learning courses. Professionally, the value is knowing how a visualization actually reaches the screen. When a dashboard with 10,000 points renders slowly, I now understand that the cost is in how many objects the GPU draws and how often the scene redraws, which is the kind of problem I can reason about instead of guessing. The habit of matching output to a reference also applies directly to analytics work, where a chart that looks good but misrepresents the scale of the data is worse than no chart.

---

## CS-340: Client/Server Development (Python/MongoDB)

Files: [`CS-340/`](./CS-340)

### Project One: CRUD Python Module
Python class that wraps PyMongo and exposes create, read, update, and delete methods for the `animals` collection in the `aac` MongoDB database. Authenticates as a dedicated `aacuser` account with read and write access to `aac` only.

### Project Two: Grazioso Salvare Dashboard *(selected portfolio artifact)*
Dash dashboard built in a Jupyter notebook. Radio-button filters select Water Rescue, Mountain or Wilderness Rescue, or Disaster or Individual Tracking dogs from the Austin Animal Center outcomes data. The filter drives an interactive data table, a chart of breeds in the result, and a Leaflet geolocation map of the selected animal. All database access goes through the Project One CRUD module. Includes the Project Two README (Word document).

### CS-340 Reflection

**How do you write programs that are maintainable, readable, and adaptable?**

I keep each piece of the program responsible for one job. The CRUD module owns the connection to MongoDB and every query. The dashboard owns the layout and the callbacks. The dashboard never imports PyMongo and never builds a connection string; it calls `db.read(query)` and gets back a list of documents. That separation paid off in two ways. First, I tested every query in the CRUD module from the shell before the dashboard existed, so when the dashboard misbehaved I knew the bug lived in the callback, not the database layer. Second, it made one real mistake easy to fix. My Module Six milestone lost points because the notebook called `shelter.read` while the starter code named the CRUD object `db`. The fix was one line, because nothing else in the notebook touched the database directly. The same module could back a Flask REST API, a scheduled script that emails a weekly intake report, or a command-line tool for shelter staff, without rewriting any query logic. The improvement I would make next is moving the username and password out of the code and into environment variables, so the module can be shared without exposing credentials.

**How do you approach a problem as a computer scientist?**

I started from the client's definitions, not from the dashboard. Grazioso Salvare defined each rescue type by specific breeds, sex, and an age range in weeks, so I turned each definition into a MongoDB query and checked the result counts in `mongosh` before writing any Python. I built the indexes around the queries the client would actually run: a single index on `breed` and a compound index on `breed` and `outcome_type`, confirmed with `explain()`. I also created the `aacuser` account with access to only the `aac` database instead of connecting as an administrator. This project differed from earlier courses because it was a full stack, from the database to the user interface, built against a real public dataset with criteria set by a client instead of a fixed exercise. For future client requests I would follow the same order: get the exact questions the client needs answered, write and test those queries first, design indexes around them, create a least-privilege database user, and build the interface last.

**What do computer scientists do, and why does it matter?**

Computer scientists turn data that already exists into tools people can act on. Grazioso Salvare trains dogs for search and rescue, and before this dashboard a trainer looking for water rescue candidates would have had to scan thousands of shelter records by hand and check breed, sex, and age for each one. The dashboard reduces that to one click, shows the matching dogs in a sortable table, and places them on a map so the trainer can see which shelter to call. That saves hours per search and cuts the chance of missing a good candidate because someone misread an intake date.

---

## CS-305: Software Security (Java/Spring Boot)

Files: [`CS-305/`](./CS-305)

### Project Two: Artemis Financial Practices for Secure Software Report *(selected portfolio artifact)*
Report documenting the security refactoring of Artemis Financial's Spring Boot web application: algorithm cipher selection, a SHA-256 checksum endpoint, a self-signed certificate and HTTPS, a secondary OWASP dependency-check scan, and functional testing of the refactored code.

### CS-305 Reflection

**The client and the problem.** Artemis Financial is a consulting company that builds individualized financial plans covering savings, retirement, investments, and insurance. Its web application uses a RESTful API, and the company wanted it modernized and secured. The specific request was a way to verify file integrity with a checksum and to protect data in transit between the client and the server, since the application handles customers' financial information.

**What I did well, and why secure code matters.** I combined manual code review with an automated scan instead of relying on either one alone. The OWASP dependency-check plug-in found known vulnerabilities in outdated libraries, while the manual review caught issues a scanner cannot see, like input that reaches the application without validation. I also kept secrets out of source code: my NVD API key lives in my Maven `settings.xml` and the project references it as `${nvd.api.key}`, so pushing the project to a public repository does not expose it. Secure coding matters most for a company like Artemis because a breach costs money, clients, and regulatory standing at the same time. IBM's 2025 Cost of a Data Breach report put the global average cost of a breach at $4.44 million, with the financial sector among the five most expensive industries. A small consulting firm cannot absorb that, so security is part of keeping the business open.

**What was challenging or helpful.** The dependency-check report was the hardest part to work with. The first run returned a long list of CVEs, and I had to learn to read CVSS scores, separate libraries the application actually uses from transitive dependencies, and recognize likely false positives. That same process turned out to be the most useful skill from the course, because reading a vulnerability report and deciding what to fix first applies to every project I will work on.

**Increasing layers of security.** I added protection at several layers so no single failure exposes the data. HTTPS with a certificate generated by Java's `keytool` encrypts traffic in transit. The SHA-256 checksum endpoint lets the client confirm a file was not altered. Updating flagged dependencies closes known holes in third-party code. In the future I would run dependency-check automatically in a CI pipeline on every pull request, add a dynamic scanner such as OWASP ZAP to test the running application, and rank mitigations by CVSS score and how exposed the affected code is, fixing internet-facing, high-severity issues first.

**Making sure the code was functional and secure.** After refactoring I ran the application and called the checksum endpoint over `https://localhost:8443` in a browser to confirm it returned the data along with its SHA-256 hash and that the certificate was served correctly. Then I reran the dependency-check scan on the refactored code and compared it with the original report to make sure my changes had not introduced new vulnerable libraries.

**Resources, tools, and practices.** The OWASP Top Ten, the OWASP dependency-check Maven plug-in, the National Vulnerability Database, Java's `keytool`, and the `MessageDigest` class for hashing. The practice I will keep using in every project is storing API keys and passwords in configuration outside the repository.

**What I would show an employer.** The Practices for Secure Software Report shows I can take an existing application, find its weaknesses, fix them, and prove the fixes worked with a before-and-after scan. The before-and-after dependency-check comparison is the clearest evidence, because it shows measurable results instead of a claim that the code is secure.

---

# Term 2026 C-4 (Jul–Aug 2026)

## CS-230: Operating Platforms (Software Design)

Files: [`CS-230/`](./CS-230)

### Project 1 — Draw It or Lose It: Executive Summary, Requirements, and Domain Model
First section of the software design document for The Gaming Room. Covers the client's business goal, four technical requirements, the design constraints those requirements impose, and a UML class diagram of the seven-class domain model in `com.gamingroom`.

### Project 2 — Platform Evaluation
Comparison of Mac, Linux, Windows, and mobile devices across three areas: hosting the game service, supporting player devices, and equipping the development team. Costed with July 2026 list prices.

### Project 3 — Completed Software Design Document *(selected portfolio artifact)*
Version 1.2 of the design document, adding the Recommendations section: operating platform, operating system architecture, storage management, memory management, distributed systems and networking, and security. This is the full document delivered to the client.

### CS-230 Reflection

The client was The Gaming Room, a studio that had built *Draw It or Lose It* as an Android-only game where teams draw and guess stock images across four one-minute rounds, with the drawing fully revealed at 30 seconds and a 15-second window for other teams to steal. They wanted a web-based version reaching Windows, macOS, and Linux desktops plus iOS and Android phones, with gameplay unchanged and only the look and feel adapting to the new platforms. Four technical requirements shaped the design: a game contains one or more teams, a team contains one or more players, game and team names must be unique so a player knows before picking a name that it is taken, and at most one instance of the game service can exist in memory at a time, with unique identifiers across every game, team, and player. My recommendation was a Java client-server application with the game engine and all state on the server, browser-based clients, and Ubuntu Server 24.04 LTS on a cloud provider as the host.

The platform evaluation is the part I did best. Rather than describing each operating system in general terms, I priced the actual decision: Windows Server 2025 Standard at roughly $1,176 per 16-core machine with Client Access Licenses adding about $45 per user, Red Hat Enterprise Linux near $800 per server per year, Mac minis at $599 apiece with MacStadium rentals around $109 a month, and Ubuntu at zero. I also found and stated that Apple discontinued macOS Server in April 2022, which settles the Mac server question on its own rather than leaving it as a matter of preference. Splitting the table into server-side, client-side, and development-tools rows let the client see where cost actually lands, and the client-side row showed the browser decision saving two full teams, since a native path would have meant Swift and Kotlin developers, App Store review, Apple's $99 annual fee, and Google's $25 registration. Every recommendation traces back to a requirement instead of resting on my own preference.

Working through the design document changed the code before I wrote it. Writing the Design Constraints section forced me to spell out the singleton mechanics in plain sentences first: a private constructor, one instance held in a private static field, and all access through a public static `getInstance()`. Putting that in words made the implementation almost mechanical. The same happened with uniqueness. Describing the constraint made it obvious that `addGame()`, `addTeam()`, and `addPlayer()` should each iterate the existing collection and return the match rather than create a duplicate, which is a different behavior from throwing an exception and one I would probably not have landed on by coding first. Drawing the UML diagram exposed a problem I could not see in prose: `Game`, `Team`, and `Player` all carried their own copies of the `id` and `name` code. Lifting them into a shared `Entity` superclass means a future rule about validating names changes one location instead of three. Writing the document also surfaced the honest weaknesses early, including that a linear name scan degrades as the number of games grows and belongs behind an indexed store in production.

If I could revise one part, it would be the last paragraph of the Domain Model section. The content is right, but the writing is not: it runs three separate ideas together, drops in a rhetorical question that does not belong in a client document, and carries typos in the exact places that matter most, `getInstnance()` instead of `getInstance()` and `ProgrammeDriver` instead of `ProgramDriver`. A developer reading that paragraph to build from could search the codebase for a method that does not exist. I would split it into one paragraph per relationship, correct the class and method names against the actual code, and replace the prose about the singleton with a short numbered list of the three mechanisms that enforce it. I would also add a sequence diagram showing a player joining a game, because the class diagram shows structure well but says nothing about the order calls happen in, and that is the question a new developer asks first.

Interpreting the user's needs meant reading past what the client asked for to what they actually cared about. "Gameplay must not change" is a sentence about experience, not architecture, and it drove one of the most important decisions in the document: the round clock runs on the server. If each browser ran its own timer, a player on a slow connection would see the drawing revealed at a different moment than everyone else, and the 15-second steal window would open unevenly. The gameplay would technically match the spec while feeling broken. Making the server the time authority keeps the 60-second round, the 30-second reveal, and the 15-second steal identical for every team regardless of device or latency. The unique-names requirement worked the same way. It reads as a data constraint, but the client's phrasing gives away the real reason, that a player should learn a name is taken before committing to it, which is a user experience problem that a database constraint alone would not solve. This matters because a design can satisfy every written requirement and still fail the people using it. Building separate native apps for five platforms would have delivered multi-platform reach exactly as requested, while costing the client two additional development teams and putting every bug fix behind App Store review.

My approach moved in one direction: requirements first, then the constraints those requirements impose, then a domain model that satisfies the constraints, then a platform evaluation, and only then a recommendation. Each layer was bounded by the one above it, so by the time I reached the recommendation there were few choices left to make arbitrarily. I would use three techniques again. First, write constraints as full sentences before drawing any classes, because a constraint you can state clearly is one you can implement. Second, build the comparison matrix with real, dated numbers before choosing anything, since a recommendation backed by list prices survives a client asking why. Third, let the requirements select the design patterns instead of picking patterns first; the singleton came from "one instance in memory" and the iterator came from "names must be unique," and neither was chosen because it was familiar. For a similar project I would add two things I skipped: a sequence diagram alongside the class diagram to capture behavior, and a short section stating what each recommendation costs, since choosing Linux buys a zero license fee and spends command-line expertise the client's staff may not have. Naming the tradeoff makes a recommendation more credible, not less.

---

## CS-255: System Analysis and Design

Files: [`CS-255/`](./CS-255)

### Project 1 — DriverPass Business Requirements Document *(selected portfolio artifact)*
Requirements document built from the client interview transcript. Covers system purpose and background, objectives, nonfunctional requirements across performance, platform, accuracy, adaptability, and security, fifteen functional requirements, user interface needs by role, plus assumptions and limitations. Includes a Gantt chart built in Lucidchart from the schedule Sam and Jennifer set during the interview.

### Project 2 — DriverPass System Design Document *(selected portfolio artifact)*
System design covering five UML models built in Lucidchart: a use case diagram with six actors and twenty use cases, two activity diagrams, a sequence diagram, and a seventeen-class class diagram. Also specifies hosting, server and client software, external integrations, backup and recovery, security and access control, operational constraints, measurable acceptance targets, and a requirements traceability table covering fifteen client needs.

### Supporting coursework
Client presentation with speaker notes, and a short paper on applying a model to the DriverPass system.

### CS-255 Reflection

The client was Liam, owner of DriverPass, a new driver-training company built around the fact that more than 65 percent of DMV driving test applicants fail. His plan was to pair online practice exams with real on-the-road instruction, and he needed a system to run it. I also interviewed Ian, his IT officer, who cared about a different set of problems. What they wanted was a web-based driver training management system reachable from any browser or phone: customers register, buy one of three packages, and book two-hour lessons that each get matched to one of ten vehicles and its assigned driver, with no double-booking. The secretary does the same booking work for customers who call or walk in. Instructors record lesson notes. Ian resets passwords and disables accounts without waiting on a developer. Liam pulls activity reports and turns a package off himself. A DMV connection feeds rule and sample-question updates into the course content so the practice tests stay current with the real test.

The part I did best is the requirements traceability table at the end of the system design document. Fifteen rows, each one naming a need stated in the interview, where it appears in the design, and the technical requirement that supports it. It turns the design from a set of drawings into something a client can audit line by line, and it caught two needs I had otherwise only half-answered. Close behind that is the consistency across the diagrams. I wrote every guard condition as an expression over an attribute that actually exists in the class diagram, so `[hoursRemaining >= 2]`, `[isActive = true]`, `[declineCount < 3]`, and `[includesOnlineClass = true]` each point at a real field rather than describing a rule in words a developer would have to interpret. The sequence diagram then uses the same guard as the activity diagram for the same decision. I also gave the design a definition of done that can be measured: 99.5 percent monthly uptime, page loads under two seconds, 200 concurrent students in the online class, 50 booking actions per minute at peak, card authorization under five seconds at the 95th percentile, and vehicle or instructor double-booking at zero occurrences verified by a nightly conflict report.

If I could revise one part, I would number the requirements in the business requirements document. Right now the fifteen functional requirements sit in an unnumbered list, which creates two problems I felt later. The traceability table in the system design document has to quote each client need in prose because there is no `FR-07` to point at, and a tester writing test cases has nothing to cite. It also let duplication slip through: the automatic forgotten-password reset appears once under the Security nonfunctional heading and again as a functional requirement, and Ian's authority to reset passwords and disable accounts appears under Adaptability and again under Security and again in the functional list. Numbering would have made those collisions visible immediately. I would label functional requirements FR-1 through FR-15 and nonfunctional ones NFR-1 onward, move every "the system shall" sentence out of the nonfunctional sections into the functional list, and leave the nonfunctional sections to describe qualities and constraints only. Then the traceability table could reference IDs, and the two documents would lock together instead of sitting next to each other.

Interpreting user needs meant separating what the client asked for from what he was trying to accomplish, and the payment design is the clearest case. Liam said to collect the card number, expiration date, and security code at registration. Taken literally, that means DriverPass stores full card numbers, which would put a small driving school into heavy PCI DSS obligations for no benefit to anyone. What Liam actually needed was to charge customers reliably and see that a payment went through. So the design sends the card straight to a tokenizing gateway and keeps only the authorization code, the last four digits, and the expiration month, which satisfies the real need and keeps the company at SAQ A scope. The audit requirement worked the same way. Liam said he wanted to know who created, changed, or cancelled a reservation, so I put the log write inside the booking flow as a fork rather than treating it as a separate feature, because a logging step that sits outside the flow is a logging step someone eventually skips. Sam's warning about offline editing produced the opposite kind of decision: allowing offline changes would create duplicate records once copies merged, so the design requires a live connection for every write and says so plainly under limitations rather than quietly dropping a capability Liam had asked about. Considering user needs matters because a system can meet every stated requirement and still leave the client worse off. Building exactly what Liam described would have handed him a card database he never wanted and did not know he was asking for.

My approach starts with the interview rather than a template. I pulled every stated need out of the transcript first, grouped them, and only then decided which were functional, which were constraints, and which were assumptions I was making on the client's behalf. From there the order was requirements, then use cases to establish scope, then activity and sequence diagrams for the two flows carrying the most branching and the most risk, then the class diagram, then the technical requirements that support all of it. Four techniques I would use again on a similar system: write guard conditions against real attribute names so the models stay consistent with each other and with the eventual code; build the traceability table while designing instead of at the end, and treat it as a checklist that exposes gaps; diagram the two or three highest-risk use cases in depth rather than diagramming all twenty shallowly; and attach numbers to acceptance criteria so "it works" has a definition both sides agree on before anyone builds. The one thing I would add next time is requirement IDs from the first draft, since almost every problem I found in revision traced back to not having them.

---

## CS-320: Software Testing, Automation, and Quality Assurance (Java/JUnit)

Files: [`CS-320/`](./CS-320)

### Project 1 — Mobile Application Services *(selected portfolio artifact: contact service)*
Java backend for a mobile application built to a client contract, covering contact, task, and appointment services. Each service validates its own fields and stores objects in memory keyed by unique ID. The portfolio artifact is the contact service: `Contact.java`, `ContactService.java`, `ContactTest.java`, and `ContactServiceTest.java`.

### Project 2 — Summary and Reflections Report *(selected portfolio artifact)*
APA-formatted report on the testing approach across all three services: requirement-to-test traceability, boundary value analysis, equivalence partitioning, and negative testing. The full suite runs 88 JUnit 5 tests with 100 percent instruction, branch, and line coverage on all six production classes as measured by JaCoCo.

### CS-320 Reflection

Keeping code functional and secure starts with validating data at the point it enters the object, so bad state is impossible to reach rather than something I check for later. In `Contact`, every field has one validation rule living in exactly one place. The constructor does not repeat those rules; it calls `setFirstName()`, `setLastName()`, `setPhone()`, and `setAddress()`, so a contact built at construction and a contact modified an hour later pass through identical checks. Security means refusing to trust the caller: every setter rejects `null` before touching the field, and `ContactService.addContact()` rejects a null contact and a duplicate ID before anything reaches the map. The `contactId` field is `final` with no setter, which matters more than it looks, because the service uses that ID as its `HashMap` key. An ID that could change after storage would leave the key and the object disagreeing, and the contact would become unreachable by the only handle the service has for it. Making the field immutable turns that whole class of bug into a compile error. For functional correctness I write a named test for each rule and assert on both sides of it. The phone number must be exactly ten digits, so I test nine digits, eleven digits, and `"12345abcde"`, which has the right length and the wrong content. JaCoCo told me every branch ran in both directions, but coverage only proves the code executed, so I paired each exception test with a positive assertion on the same rule.

Interpreting user needs means turning the requirement document into a checklist before writing anything. Every "shall" statement became at least one named test, and the test name repeats the requirement in plain words. The rule that an address shall be no longer than 30 characters became `testAddressTooLongThrowsException` at 31 characters and `testAddressAtMaxLengthIsValid` at exactly 30. Anyone reading the test list can see which requirement each test defends, and no requirement sits there without a test that would fail if its rule broke. Reading closely matters as much as reading everything. "Exactly ten digits" and "no more than ten characters" are different constraints, and that difference is why phone gets a `\d{10}` pattern match while first name gets a length check. I also paid attention to what the requirements did not ask for. No user interface and no database meant `HashMap` storage was the honest answer rather than a shortcut, and building a persistence layer nobody requested would have added risk without adding value. The hardest part was catching my own bias. Once I had written `\d{10}`, my instinct was to test digit counts and stop, because I already knew what the code did, so I wrote my test cases from the requirement text before rereading my implementation. That is how the letters case got written at all.

My approach to design starts by asking what owns each rule, then giving that responsibility exactly one home. `Contact` owns whether a phone number is valid. `ContactService` owns whether an ID is unique and where contacts live. The service's update methods are one line each because they delegate straight to the object's setters, which means there is no path through the service that skips validation. When responsibilities blur, the same rule ends up written in three places and two of them are wrong. I also design for testability from the start, and it changes the code. `ContactService` keeps no static state, so `@BeforeEach` hands every test a clean instance and no test depends on execution order. Nothing reaches for a clock, a network, or a file, so the suite finishes in about half a second, and that speed is a design outcome rather than a happy accident, because a slow suite is a suite people stop running. Small choices carry the same logic: `getContact()` throws on a missing ID instead of returning `null`, which pushes the failure to the caller immediately rather than three lines later at a `NullPointerException` that says nothing useful. I write tests in the same commit as the code they cover, because the cheapest moment to write a test is while the requirement is still in my head. Skipping one trades a minute now for a defect that hides for months.

---

# Term 2026 C-3 (May–Jun 2026)

## CS-210: Programming Languages (C++)

Files: [`CS-210/`](./CS-210)

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

Files: [`CS-250/`](./CS-250)

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

Files: [`DAD-220/`](./DAD-220)

### Project 1 — QuantigrationUpdates Database
Built a MySQL relational database (`QuantigrationUpdates`) with Customers, Orders, and RMA tables. Ran queries, performed DML operations, renamed tables/columns, and exported data to CSV.

### Project 2 — Quantigration RMA Analysis
Analyzed return merchandise authorization data using SQL: counted returns by U.S. state and calculated percentage of returns by product type.

---

*Southern New Hampshire University | Bachelor of Science in Computer Science*

---

*AI usage acknowledgment: Anthropic's Claude was used to assist with organizing and drafting the reflection responses in this README.*
