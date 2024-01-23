# Pizza Management System

<p align="center">
<img src="https://socialify.git.ci/Mohid-Anwar/Pizza-Management-System-DSA/image?font=KoHo&language=1&name=1&owner=1&pattern=Brick%20Wall&theme=Auto" alt="Pizza-Management-System-DSA" width="640" height="320" />
</p>

  ## Table of Contents
- [Description](#description)
- [Caution for User Inputs](#caution-for-user-inputs-🚨)
- [Data Structures](#data-structures)
  - [Doubly Customer Linked List](#doubly-customer-linked-list)
  - [Graph (Sectors)](#graph-sectors)
  - [Feedback Stack](#feedback-stack)
  - [Cancellation Queue](#cancellation-queue)
- [Functionalities](#functionalities)
  - [Starting Menu](#starting-menu)
  - [Customer](#customer)
    - [Ordering](#ordering)
    - [Display of Menu](#display-of-menu)
    - [Display details of Customer](#display-details-of-customer)
    - [Give Feedback](#give-feedback)
    - [Cancel an Order](#cancel-an-order)
    - [Go Back to Main Menu](#go-back-to-main-menu)
  - [Admin](#admin)
    - [Display All](#display-all)
    - [Deliver a Bunch of Orders](#deliver-a-bunch-of-orders)
    - [Delete Customer](#delete-customer)
    - [Display All Customers](#display-all-customers)
    - [Look at Pending Feedbacks](#look-at-pending-feedbacks)
    - [Look at Canceled Order Queue](#look-at-canceled-order-queue)
    - [Go Back to Main Menu](#go-back-to-main-menu)
- [Contribution Guidelines](#-contribution-guidelines)
- [Built with](#💻-built-with)

## Description
Our code is a Pizza Shop Management System allowing users to place orders to specific locations. The system stores all customers and their respective orders. The system is divided into Admin and User sections, and all accounts are password-protected.

### Caution for User Inputs 🚨
Please enter inputs with caution as they directly affect the system's functionality.

### Colorful CLI Interface
The CLI app features a colorful interface for an enhanced user experience.

### Data Structures

#### Doubly Customer Linked List
Each customer node includes:
- Name
- Password
- Unique ID
- Next and Previous pointers
- First Order pointer

Each customer has a respective order list attached to it.

#### Graph (Sectors)
The Graph structure contains sectors and a respective adjacency matrix contains the distance to each sector.

#### Feedback Stack
The Feedback Stack stores user feedback and operates like a notification bar.

#### Cancellation Queue
The Cancellation Queue stores canceled orders, similar to notifications.

## Functionalities

### Starting Menu
The initial menu determines whether the user is an Admin or a customer. It also allows exiting the program. After proper credentials, users are logged in, and signup is available.

### Customer

#### Ordering
Details are acquired, and the destination sector is provided. Dijkstra's Algorithm calculates the shortest path, and the new order's details are displayed. A copy of the order is added to a Priority Queue for later delivery.

#### Display of Menu
Displays all menu items and respective prices.

#### Display details of Customer
Displays logged-in customer details and their orders.

#### Give Feedback
Feedback and additional comments are acquired and pushed into a stack.

#### Cancel an Order
User enters Order ID, and the order is removed from the doubly list and added to the canceled Order Queue.

#### Go Back to Main Menu
Takes the user back to the Starting Menu screen.

### Admin

#### Display All
Displays all customers with their respective orders.

#### Deliver a Bunch of Orders
Delivers all pending orders.

#### Delete Customer
Searches for the customer using the customer ID and deletes it from the doubly list.

#### Display All Customers
Displays customers who have signed up without their respective orders.

#### Look at Pending Feedbacks
Displays and pops the stack containing feedback.

#### Look at Canceled Order Queue
Displays and removes canceled orders from the Order Queue.


#### Go Back to Main Menu
Takes the user back to the Starting Menu screen.


# 🍰 Contribution Guidelines:</h2>

Contributions are welcome! Fork the repository and submit a pull request.
  
# 💻 Built with

Technologies used in the project:

*   C++
*   VS Code
