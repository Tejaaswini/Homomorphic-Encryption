
# **Homomorphic Encryption for Financial Data Processing**

## **Project Overview**

This project demonstrates the application of homomorphic encryption (HE) to perform SQL-like operations on encrypted financial data. The primary goal is to showcase the feasibility of using homomorphic encryption to secure sensitive data while still enabling essential database operations such as `SELECT`, `SUM`, and `UPDATE`.

### **Key Features**
- **Encryption of Financial Data:** Securely encrypts financial data, such as account balances, using the BFV scheme.
- **Homomorphic Operations:** Perform encrypted SQL-like operations (SELECT, SUM, UPDATE) without decrypting the data.
- **Performance Analysis:** Tracks and reports the number of arithmetic operations (additions and multiplications) required for each operation, providing insights into the computational overhead.

## **Prerequisites**

Before running the project, ensure you have the following installed:

- **C++ Compiler:** A C++17 compatible compiler.
- **CMake:** Version 3.12 or higher.
- **Microsoft SEAL:** The Microsoft SEAL library is required for homomorphic encryption.

## **Installation**

### **1. Clone the Repository**
```bash
git clone https://github.com/Tejaaswini/Homomorphic-Encryption
cd Homomorphic-Encryption
```

### **2. Install Microsoft SEAL**

Follow the instructions from the [Microsoft SEAL GitHub repository](https://github.com/microsoft/SEAL) to install the SEAL library on your system.

### **3. Build the Project**
```bash
mkdir build
cd build
cmake ..
make
```

### **4. Run the Application**
```bash
./homomorphic_encryption_example
```

## **Usage**

### **1. Encryption Scheme**
The project uses the **BFV scheme** (Brakerski/Fan-Vercauteren) for homomorphic encryption, which supports both addition and multiplication operations on encrypted integers.

### **2. Financial Data Processing**

The project simulates a financial database containing account balances. It allows you to perform the following operations on encrypted data:

- **SELECT Operation:** Filters account balances based on a condition (e.g., balances greater than $10,000).
- **SUM Operation:** Computes the total sum of the selected account balances.
- **UPDATE Operation:** Increases the balance of selected accounts by a fixed amount (e.g., $500).

### **3. Operation Performance Analysis**
The application tracks the number of addition and multiplication operations performed during each SQL-like operation. These counts are displayed after each operation to provide insights into the computational overhead introduced by homomorphic encryption.

## **Example Output**
Running the program will generate output similar to the following:

```
***********************************************************************
********** Homomorphic Encryption: SELECT and COUNT Operations **********
***********************************************************************
Plaintext matrix slot count: 4096
Account balances have been encrypted.
Result of SELECT operation (balances > $10,000): 12000 0 50000 0 30000 0 20000 0 60000 15000
Total sum of balances > $10,000: $187000
Updated account balances (after increasing by $500 for balances > $10,000): 12500 0 50500 0 30500 0 20500 0 60500 15500
Total Additions: 56789
Total Multiplications: 34567
Total Operations (Additions + Multiplications): 91356
```

## **Project Structure**

- `main.cpp`: Contains the implementation of the homomorphic encryption operations (SELECT, SUM, UPDATE).
- `CMakeLists.txt`: CMake configuration file for building the project.
- `README.md`: This file.

## **Contributing**

If you'd like to contribute to this project, feel free to fork the repository and submit a pull request. Contributions are welcome!

## **License**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## **Acknowledgments**

- **Microsoft SEAL:** This project uses the Microsoft SEAL library for homomorphic encryption. Special thanks to the SEAL team for their excellent work.

## **Contact**

For any questions or feedback, please contact [tejaaswini.narendran@gwu.edu] or [akshay.nayak@gwu.edu].
