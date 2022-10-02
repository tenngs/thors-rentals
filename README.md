![](Images/Thor's_Arctic_Equipment_Rentals.png)


## Background
(** fictional backstory start ** - please do NOT read if you just want info about the repo**)<br>
<br>
Thor held a high-flying job at a Magic Circle law firm in London for the best part of the past two decades. It made him incredibly wealthy on the outside, however, somewhat hollow on the inside due to the job-related pressure he experienced daily. Hence, he decided to quit his job, liquidate all his stock market positions and sell his home to move to somewhere where air is fresh and life-induced stress is minimal. After a brief search, Thor settled in Zermatt, Switzerland.<br>
Having enjoyed for a while everything that beautiful Switzerland has to offer, Thor decided once again to enter the working world by the virtue of opening a business. Naturally, the nature of Thor's business should have something to do with the quirks of his new-found surroundings. Thus, he decided to open an arctic equipment rental business and name it imaginatively "Thor's Arctic Equipment Rentals".<br>After purchasing a plethora of new equipment, he thought to himself: "How on Earth am I going to keep track of all this gear with customers renting and returning things all the time?" <br>
After a period of deep frustration, Thor had an astonishing idea! "Ha!", said Thor to himself and continued: "A software system to keep track of customers, staff, rental income, outgoing and incoming equipment and such must be the way forward!"<br>
Luckily for Thor, he had just the right person in mind to help him. Thor could not contain his enthusiasm when he picked up his shiny new iPhone and dialled a number recovered from the confines of his impossibly enormous contact list.<BR>
"Hel-lo?", said the slightly weary voice on the other end of the line clearly wondering who on Earth would call from Switzerland at this hour.<br> "@tenngs? Drop whatever nonsense you are doing right now! I have an urgent mission for you..." <br><br>
(**fictional backstory end **)

## What does it do?
Thor's Rentals provides an arctic rental equipment management system which is aimed to be utilised by a rental shop staff member. Currently, Thor's stocks skis, snowboards and ATVs. It allows for adding customers, granting system access for existing staff members, adding rental items, managing outgoing and incoming rental equipment and providing inventory and business-related statistics. The system further provides moderate to high user input validation and a login facility.<br><br>
TL;DR add customers, staff, equipment, calculate when equipment is due back and update inventory.

## How does it do that?
Thor's Rentals 90s-inspired and ASCII Art-rich user interface interacts with thors_rentals sqlite3 database containing various tables where information can be added to and retrieved from. For example, adding a customer involves gathering customer details and saving them into a table in the database and logging in involves querying a database to validate login credentials.<br>
Furthermore, the system keeps track about when rental items are due to be returned and the state of current inventory by retrieving information from a database and computing the result when requested.<br><br>
TL;DR "old-school" UI interacts with sqlite3 database to write, retrieve and compute rental-related stuff.

## Tech stack?
C++ and sqlite3

## OK, but why?
I have a passion for C++ language. Whilst contemplating a project idea, I came across a myriad of car rental, hospital and student management systems made by others. I also wanted to make a management system of some sort, but simultaneously one that is not so common and fits my preferences.

## Let's have a look-see, shall we?

// login


// init rental

// receive rental

// stats?
