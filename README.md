
# Patient Management System
This is a mini-project for the Algorithms 101 course at CamTech University.

## Overview

The Patient Management System is designed to manage patient records, including their personal information, diagnosis, prescribed medicines, and medical history. The system is built using C programming and uses a CSV file format for exporting data, which can be easily viewed in Microsoft Excel or Google Sheets.

## Features

+ Add Patient (Doctor Only): Allows the addition of new patient records, including personal details, diagnosis, and medical history.
+ Add Medicine to Patient (Doctor Only): Doctors can prescribe medicines to patients, including dosage details, intake times, and specific advice.
+ View Patient Info: Patients or doctors can view detailed information about a patient by entering their ID.
+ Export Patient Data to CSV: The system allows exporting all patient data to a CSV file, which can be imported into Excel or Google Sheets for further analysis.
+ Search Patient: Allows searching for patients by name, diagnosis, or prescribed medicines.
+ Report Common Diagnoses: Provides a count of patients with a specific diagnosis.

## How to Run
1. Clone or Download the Repository:

+ Clone the repository or download the code files to your local machine.

2. Compile the code :
+ Use any C compiler (e.g., GCC) to compile the code. For example :
```
gcc patient_management_system.c -o patient_management_system
```

3. Run the Executable :
+ Execute the compile file :
```
./patient_management_system
```
4. Using the System:

+ Follow the on-screen menu to add patients, prescribe medicines, view patient info, export data to CSV, search patients, and report diagnoses.
5. Exporting to Excel/Google Sheets:

+ After exporting the data to a CSV file, open Excel or Google Sheets, and import the CSV file to view the patient data.

## Improvement
+ Graphical User Interface (GUI): Implementing a GUI could make the system more user-friendly, especially for non-technical users.
+ Database Integration: Replacing the CSV file with a relational database like MySQL or SQLite would improve data management and scalability.
+ Enhanced Search Functionality: Adding advanced search filters, such as date ranges or multi-criteria searches, could improve the usability of the search feature.
+ User Authentication: Implementing a login system to restrict access to certain features (e.g., only doctors can add patients or prescribe medicines) would increase security.

## Challenges Faced
+ Structuring Data: One of the initial challenges was designing the data structures to manage patients, medicines, and their relationships efficiently.
+ CSV Export: Managing the export of complex data structures (e.g., nested medicines within a patient record) to a CSV file required careful formatting.
+ Input Handling: Ensuring that user inputs, especially strings and integers, are correctly handled to prevent crashes or incorrect data entries.
+ Medicine Management: Implementing the functionality to allow for multiple medicines per patient while ensuring data integrity and ease of use.
+ Debugging: Debugging and testing the system to handle edge cases, such as maximum limits on patients and medicines, was crucial to ensuring the system's reliability.

## Credit 
Developed by KOKOMA Team.

If you have any questions or encounter any issues, feel free to reach out to me at CamTech University.

Thank you !  
(✿◠‿◠)


