[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jIKk4bke)
# CS210 Data Structures SP25
## Programming Assignment 2: Text-Based RPG Using Decision Trees

### **Student Name:** `Jake Marra`  
### **Student ID:** `827952717`  

---

## **1. Project Overview**

> This project includes a text-based RPG using a **binary decision tree**. Each game event is represented as a node, and their contents are stored in `eventMap`. The player progresses by picking decision 1 or 2, eventually getting to an ending. The storyline is loaded from an external text file called `story.txt` which is parsed to construct the deciison tree. The game ends when a leaf node is reached, indicating the player has no more choices to make.

---

## **2. Folder & File Structure**
(Explain the role of each file in your project.)

- **`main.cpp`** → `Acts as the entry point of the text-based RPG game`  
- **`GameDecisionTree.h`** → `Acts as the core engine of the program. Parses the txt file into nodes as well as connects and traverses nodes`  
- **`Node.h`** → `A template class that stores story elements and their connections`  
- **`Story.h`** → `Defines the data structure that holds all story content and navigation logic`  
- **`story.txt`** → `Contains a text file of the story and their choices`  

---

## **3. Decision Tree Construction**

`Story` objects are created from the text file via the delimiters. The delimiters, or "|", split 
each line of `story.txt` into 4 parts:
- The description of the current path
- The event number of the current path
- The left event number
- The right event number

I use a map called `eventMap` to track all nodes by their event numbers. For each object a `Node<Story>`is created to hold it, and at the same time, a new node is added to `eventMap` with its event number as the key.
When all nodes are created from one line, the tree will connect the children by looking up each node's `leftEventNumber` and `rightEventNumber`. 

If an event has `-1` as either a left or right child, it indicates that there are no further choices on that path, and ends the story, printing `"THE END"`. At this point the program will terminate as well, since there is no more story to generate.

---

## **4. Game Traversal**

At each node, beginning from node one, the program will display the `description` part of the `story.txt` line and then ask you to choose either decision 1 or 2 that are listed from `description`. If the player writes anything besides 1 or 2, the program will say the input is invalid, and request that the user restart the program and input the proper values. If they input 1 or 2, then the adventure will continue and the program will pick the path the player has chosen.

When the player approaches a leaf node, marked by `-1` in `story.txt`, it means there are no more choices for the player to make, so a message saying `"THE END"` will show, and the program will terminate successfully. 

I have a singular special case in my program where two separate choices lead to event 6. I deal with this overlap by only creating a single instance of event 6 and have events 3 and 4 point to the same node in memory, which doesn't cause me any errors.

---

## **5. File Parsing & Data Loading**

First my `loadMemoryFromFile` function checks if `story.txt` can even be opened in the first place. If not, it returns an error and the program terminates. If it CAN be read, then it takes each line from `story.txt` and parses it into 4 different components using the "|" delimiter:
- eventStr: the node's unique ID that is used in choices
- descStr: the line's story text that is displayed to the user
- leftStr: the destination of the left choice
- rightStr: the destination of the right choice

Once these components are defined, all strings are then converted into integers using `stoi()` and all empty strings default to `-1`. Once all is said and done, a `Story` object is created with said data.All nodes called `Node<Story>` are then stored in `eventMap`. The first node, or `eventNum == 1`, is set as the root node. It is where the story starts. 

I had some issues properly connecting nodes based off this event number system, so I made a new function titled `connectNodes()` that will perform this function easier. This function ensures all nodes are properly linked together (hopefully) without error.

---

## **6. Debugging Process (Errors & Fixes)**

I was having the hardest time getting my `story.txt` file to properly read. I spent, like, maybe a good 3 hours on my `loadMemoryFromFile` function freaking out because I kept getting exit code 0 but it just would refuse to read my txt file no matter what I did. Turns out it was because I just had the `story.txt` file in the wrong location so there was no file to read in the first place. Felt so stupid when I moved the file and it worked instantly. I love programming

---

## **7. Sample Output & Walkthrough**
(Provide an example of how the game runs, including player input.)
1. The game first loads the content from `story.txt` and builds the tree. It then sets event 1 as the root, and shows `descStr` to the player.
2. The game then asks the player to input either 1 or 2 to submit their path choice, which are shown from `descStr`. If anything other than 1 or 2 is picked, the program terminates, and requests the player reset the program and input values properly.
3. If 1 or 2 are picked, then the story will traverse, moving to each event node until an ending is reached (indicated by a leaf node)
4. No matter what the player does, a leaf node will always be reached, as every story choice eventually leads to an end. Once a leaf node is reached, the program will terminate, printing "THE END" indicating that an ending was reached.

---

## **8. Big-O Analysis of Core Methods**
(Analyze the complexity of key methods.)

- **Loading the tree from the file** → `O(N)`  
- **Searching for an event in the tree** → `O(1)`  
- **Game traversal efficiency** → `O(N)`  

---

## **9. Edge Cases & Testing**

I added a few lines of code that make sure the player properly inputs either 1 or 2 to traverse the tree and continue the story. At first I had it be a while loop, but I kept getting infinite loop errors, so I opted for just a single if function that terminates the program if the input isn't 1 or 2. Worked much better.

---

## **10. Justification of Additional Features (If Any)**

I don't know if this necessarily counts as an "extra feature", but I added a few more functions to make sure my program executed properly, like `connectNodes()` for example. It it counts for extra credit, then awesome!!!
---

## **Final Notes**
- **README is mandatory** → `(-10 points deduction if missing).`  
- **Code must compile and run** → `(Code that does not run will receive a 0).`  
- **Do not modify provided skeleton code** → `(You may only add to it).`  

---
