# Tourist Accommodation Management.
This program was written together with @gabrieljtmelo in the C# programming language and is designed to manage tourist accommodation. It includes various functions related to the management of room rentals, such as the visualization of data on rentals made by clients, a list of available rooms, the possibility of removing, changing and inserting rooms by saving them in files, among others. The program also allows you to create and store accounts for use with the software.

# Prerequisites
To run this program in C#, you will need to have .NET Core installed on your computer. Use an integrated development environment (IDE) such as Visual Studio or Visual Studio Code to edit the source code.

# How to use
- Download or clone the repository on your computer.
- Open the Program.cs file in your IDE.
- Compile and run the program.
- When you run the program, simply log in and choose between Host and Hotel, and use the software.

# Files
The project consists of the following files:
- Program.cs: This is the project's main file, which contains the main() function and the program menu. Here, interactions with the user are managed, and the program's main functionalities are invoked.
- Hospede.cs: This file contains the definition of the Hospede class, which is a child class of Utilizador. It represents a guest in the system, with specific characteristics and methods related to an individual staying at the hotel.
- Hotel.cs: The Hotel.cs file contains the definition of the Hotel class, also a child of Utilizador. This class represents a hotel in the system, including its properties and associated methods, allowing the management of information related to the hotel.
- Quarto.cs: In this file, the Quarto class is defined. This class represents a room in the context of the program, and its functions include manipulating room-specific information such as type, availability, etc.
- Reserva.cs: Here, the Reserva class is defined to represent a reservation in the system. This file contains methods and properties related to managing reservations, including associating reservations with rooms and guests.
- Utility.cs: This file contains utility functions that can be used throughout the program. Common functions that are not directly linked to a specific class can be found here, providing modularity and code reuse.
- Utilizador.cs: The Utilizador.cs file contains the definition of the User parent class, which serves as the basis for the Host and Hotel classes. It can contain properties and methods common to both types of users in the system.
