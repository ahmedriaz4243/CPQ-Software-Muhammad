# CPQ Software

CPQ Software is a **desktop application** built with C++ and SQLite for configuring, pricing, and quoting (CPQ) products. The application features an intuitive user interface for creating, viewing, editing, and deleting quotes, along with a database backend for persistent storage of quote data.

## Features

- **Create Quotes**: Easily create new quotes by entering the quote name, customer name, material, size, and price.
- **View Quotes**: View all existing quotes in a structured format.
- **Edit Quotes**: Modify existing quotes with new information.
- **Delete Quotes**: Remove quotes that are no longer needed.
- **Persistent Storage**: Uses SQLite for storing quote data, ensuring data is saved between sessions.

## Getting Started

### Prerequisites

- Windows OS
- [SQLite](https://www.sqlite.org/download.html)

### Building the Project

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/yourusername/cpq-software.git
    ```
2. **Open the Project**:
    Open the project in your preferred C++ development environment (e.g., Visual Studio).

3. **Build the Project**:
    Build the project to generate the executable.

### Running the Application

- Run the executable generated in the build step to start the CPQ Software application.

## Usage

1. **Launching the Application**:
    - Click the executable file to launch the application.

2. **Creating a Quote**:
    - Click on "Create Quote" button.
    - Enter the required details: Quote Name, Customer Name, Material, Size.
    - Click "OK" to save the quote.

3. **Viewing Quotes**:
    - Click on "View All Quotes" button to see all stored quotes.

4. **Editing a Quote**:
    - Click on "Edit Quote" button.
    - Select the quote to edit by its number.
    - Enter new details and click "OK" to update the quote.

5. **Deleting a Quote**:
    - Click on "Delete Quote" button.
    - Enter the quote number to delete and confirm.
    
6. **DB file**:
    - The 'quotes.db' file is a simple database file that will be created in the same directory.
    
## Contributing & Feedback

Contributions are welcome! Please fork the repository and submit pull requests for any enhancements or bug fixes.

## Acknowledgments

- SQLite for providing a simple and efficient database solution.
- The C++ community and Microsoft Learn for providing valuable resources for desktop development..

