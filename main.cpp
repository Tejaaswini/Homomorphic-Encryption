#include "seal/seal.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace seal;

void print_banner(string title)
{
    if (!title.empty()) {
        size_t title_length = title.length();
        size_t banner_length = title_length + 2 * 10;
        string banner_top(banner_length, '*');
        string banner_middle = string(10, '*') + " " + title + " " + string(10, '*');
        cout << endl << banner_top << endl << banner_middle << endl << banner_top << endl;
    }
}

void homomorphic_encryption()
{
    print_banner("Homomorphic Encryption: SELECT, SUM, and UPDATE Operations for Financial Data");

    EncryptionParameters parms(scheme_type::bfv);
    size_t poly_modulus_degree = 4096;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));

    parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 20));

    SEALContext context(parms);

    auto context_data = context.first_context_data();
    if (!context_data->qualifiers().using_batching) {
        throw std::invalid_argument("encryption parameters are not valid for batching");
    }

    KeyGenerator keygen(context);
    PublicKey public_key;
    keygen.create_public_key(public_key);
    SecretKey secret_key = keygen.secret_key();
    
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);

    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    BatchEncoder batch_encoder(context);
    size_t slot_count = batch_encoder.slot_count();

    cout << "Plaintext matrix slot count: " << slot_count << endl;

    vector<uint64_t> account_balances = { 12000, 8500, 50000, 7500, 30000, 4500, 20000, 10000, 60000, 15000 };
    Plaintext plain_matrix;
    batch_encoder.encode(account_balances, plain_matrix);

    Ciphertext encrypted_matrix;
    encryptor.encrypt(plain_matrix, encrypted_matrix);

    cout << "Account balances have been encrypted." << endl;

    // initialize operation counters
    int add_count = 0;
    int mult_count = 0;

    // perform a homomorphic SELECT operation (e.g., select balances > $10,000)
    vector<uint64_t> select_mask = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 };
    Plaintext plain_select_mask;
    batch_encoder.encode(select_mask, plain_select_mask);

    Ciphertext encrypted_select_mask;
    encryptor.encrypt(plain_select_mask, encrypted_select_mask);

    // homomorphic multiplication by applying the select mask
    evaluator.multiply_inplace(encrypted_matrix, encrypted_select_mask);
    mult_count++;

    evaluator.relinearize_inplace(encrypted_matrix, relin_keys);
    add_count++;

    Plaintext plain_result;
    decryptor.decrypt(encrypted_matrix, plain_result);

    vector<uint64_t> result;
    batch_encoder.decode(plain_result, result);

    cout << "Result of SELECT operation (balances > $10,000): ";
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;

    // perform a homomorphic SUM operation
    uint64_t total_sum = 0;
    for (size_t i = 0; i < result.size(); i++)
    {
        total_sum += result[i];
        add_count++;
    }
    cout << "Total sum of balances > $10,000: $" << total_sum << endl;

    // perform a homomorphic UPDATE operation
    Plaintext plain_update_amount;
    batch_encoder.encode(vector<uint64_t>(slot_count, 500), plain_update_amount);

    Ciphertext encrypted_update_amount;
    encryptor.encrypt(plain_update_amount, encrypted_update_amount);

    evaluator.add_inplace(encrypted_matrix, encrypted_update_amount);
    add_count++;

    decryptor.decrypt(encrypted_matrix, plain_result);
    batch_encoder.decode(plain_result, result);

    cout << "Updated account balances (after increasing by $500 for balances > $10,000): ";
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;

    cout << "Total Additions: " << add_count << endl;
    cout << "Total Multiplications: " << mult_count << endl;
    cout << "Total Operations (Additions + Multiplications): " << add_count + mult_count << endl;
}

int main()
{
    homomorphic_encryption();
    return 0;
}
