#include "verademo_vulns.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include <memory>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <csignal>

// Platform-specific includes
#ifdef _WIN32
    #include <io.h>
    #include <direct.h>
    #include <sys/stat.h>
    #define popen _popen
    #define pclose _pclose
    #define access _access
    #define F_OK 0
    #define getcwd _getcwd
    #define chmod _chmod
#else
    #include <unistd.h>
    #include <sys/stat.h>
#endif

// Simple MD5 stub
namespace SimpleMD5 {
    std::string md5(const std::string& input) {
        unsigned int hash = 5381;
        for (char c : input) {
            hash = ((hash << 5) + hash) + c;
        }
        std::stringstream ss;
        ss << std::hex << hash;
        return ss.str();
    }
}

// CWE-89: SQL Injection in login
bool UserController::login_vulnerable(const std::string& username, const std::string& password) {
    std::cout << "[UserController::login_vulnerable] Processing login\n";
    std::string password_hash = CryptoUtils::md5_hash_vulnerable(password);
    std::string sql_query = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password_hash + "';";
    std::cout << "[DEBUG] SQL: " << sql_query << "\n";
    std::string result = execute_sql_query(sql_query);
    return !result.empty();
}

// CWE-89: SQL Injection in password hint
std::string UserController::get_password_hint_vulnerable(const std::string& username) {
    std::cout << "[UserController::get_password_hint_vulnerable]\n";
    std::string sql = "SELECT password_hint FROM users WHERE username = '" + username + "'";
    std::cout << "[DEBUG] SQL: " << sql << "\n";
    return execute_sql_query(sql);
}

// CWE-89: SQL Injection in registration
bool UserController::register_user_vulnerable(const std::string& username, const std::string& password,
                                               const std::string& real_name, const std::string& blab_name) {
    std::cout << "[UserController::register_user_vulnerable]\n";
    std::string password_hash = CryptoUtils::md5_hash_vulnerable(password);
    std::string sql = "INSERT INTO users VALUES('" + username + "','" + password_hash + "','" + real_name + "','" + blab_name + "')";
    std::cout << "[DEBUG] SQL: " << sql << "\n";
    execute_sql_query(sql);
    return true;
}

// CWE-89: SQL Injection in user history
std::vector<std::string> UserController::get_user_history_vulnerable(const std::string& username) {
    std::cout << "[UserController::get_user_history_vulnerable]\n";
    std::string sql = "SELECT event FROM users_history WHERE blabber=\"" + username + "\"";
    std::cout << "[DEBUG] SQL: " << sql << "\n";
    std::vector<std::string> events;
    events.push_back(execute_sql_query(sql));
    return events;
}

// CWE-89 + CWE-564: SQL Injection in ORDER BY
std::vector<User> BlabController::get_blabbers_vulnerable(const std::string& username, const std::string& sort_column) {
    std::cout << "[BlabController::get_blabbers_vulnerable]\n";
    std::string sql = "SELECT * FROM users WHERE username!='" + username + "' ORDER BY " + sort_column;
    std::cout << "[DEBUG] SQL: " << sql << "\n";
    execute_sql_query(sql);
    return std::vector<User>();
}

// CWE-78: Command Injection in ping
std::string ToolsController::ping_vulnerable(const std::string& host) {
    std::cout << "[ToolsController::ping_vulnerable] host=" << host << "\n";
    std::string command = "ping -c1 " + host;
    std::cout << "[DEBUG] CMD: " << command << "\n";
    return execute_command(command);
}

// CWE-78: Command Injection in fortune
std::string ToolsController::fortune_vulnerable(const std::string& fortune_file) {
    std::cout << "[ToolsController::fortune_vulnerable]\n";
    std::string cmd = "/usr/games/fortune " + fortune_file;
    std::cout << "[DEBUG] CMD: " << cmd << "\n";
    return execute_command(cmd);
}

// CWE-327: Weak MD5 hashing
std::string CryptoUtils::md5_hash_vulnerable(const std::string& input) {
    return SimpleMD5::md5(input);
}

// CWE-73: Path Traversal
std::string FileController::download_profile_image_vulnerable(const std::string& image_name) {
    std::cout << "[FileController::download_profile_image_vulnerable]\n";
    std::string path = "/var/www/resources/images/" + image_name;
    std::cout << "[DEBUG] PATH: " << path << "\n";
    std::ifstream file(path);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    return "[ERROR] File not found";
}

// CWE-611: XXE
std::string XMLParser::parse_xml_vulnerable(const std::string& xml_content) {
    std::cout << "[XMLParser::parse_xml_vulnerable]\n";
    std::cout << "[DEBUG] XML: " << xml_content.substr(0, 100) << "\n";
    return "[XML parsed - XXE vulnerable]";
}

// ============================================================================
// CWE-119/120/121/122: Buffer Overflow Vulnerabilities
// ============================================================================

// CWE-120: Buffer Copy without Checking Size of Input (strcpy)
void BufferOverflowVulns::unsafe_string_copy(const char* user_input) {
    std::cout << "[BufferOverflowVulns::unsafe_string_copy]\n";
    
    /* START VULNERABILITY - CWE-120: strcpy Buffer Overflow */
    char buffer[32];
    strcpy(buffer, user_input);  // VULNERABLE: No bounds checking
    /* END VULNERABILITY */
    
    std::cout << "[DEBUG] Copied to buffer: " << buffer << "\n";
}

// CWE-134: Uncontrolled Format String
void BufferOverflowVulns::format_string_vulnerability(const char* user_input) {
    std::cout << "[BufferOverflowVulns::format_string_vulnerability]\n";
    
    /* START VULNERABILITY - CWE-134: Format String Vulnerability */
    char output[256];
    sprintf(output, user_input);  // VULNERABLE: User controls format string
    printf(user_input);           // VULNERABLE: Direct printf of user input
    /* END VULNERABILITY */
    
    std::cout << "[DEBUG] Formatted output\n";
}

// CWE-121: Stack-based Buffer Overflow
void BufferOverflowVulns::stack_buffer_overflow(const char* user_data) {
    std::cout << "[BufferOverflowVulns::stack_buffer_overflow]\n";
    
    /* START VULNERABILITY - CWE-121: Stack Buffer Overflow */
    char local_buffer[64];
    strncpy(local_buffer, user_data, 200);  // VULNERABLE: Copies more than buffer size
    local_buffer[63] = '\0';
    
    // Another vulnerability with sprintf
    char formatted[50];
    sprintf(formatted, "User input: %s", user_data);  // VULNERABLE: No bounds check
    /* END VULNERABILITY */
    
    std::cout << "[DEBUG] Buffer contents: " << local_buffer << "\n";
}

// CWE-122: Heap-based Buffer Overflow
char* BufferOverflowVulns::heap_buffer_overflow(const char* input) {
    std::cout << "[BufferOverflowVulns::heap_buffer_overflow]\n";
    
    /* START VULNERABILITY - CWE-122: Heap Buffer Overflow */
    char* heap_buffer = (char*)malloc(32);
    strcpy(heap_buffer, input);  // VULNERABLE: No size check on heap buffer
    /* END VULNERABILITY */
    
    std::cout << "[DEBUG] Heap buffer allocated and filled\n";
    return heap_buffer;
}

// CWE-126: Buffer Over-read
void BufferOverflowVulns::buffer_overread(const char* data, int length) {
    std::cout << "[BufferOverflowVulns::buffer_overread]\n";
    
    /* START VULNERABILITY - CWE-126: Buffer Over-read */
    char internal_buffer[50];
    // Copy without checking if length exceeds data size
    memcpy(internal_buffer, data, length);  // VULNERABLE: length not validated
    internal_buffer[49] = '\0';
    
    // Reading beyond buffer bounds
    for (int i = 0; i < length + 10; i++) {  // VULNERABLE: Reads past buffer
        char c = data[i];
        (void)c;  // Suppress unused warning
    }
    /* END VULNERABILITY */
    
    std::cout << "[DEBUG] Buffer read complete\n";
}

// CWE-676: Use of Potentially Dangerous Function
void BufferOverflowVulns::dangerous_function_usage() {
    std::cout << "[BufferOverflowVulns::dangerous_function_usage]\n";
    
    /* START VULNERABILITY - CWE-676: Dangerous Functions */
    char input_buffer[100];
    char output_buffer[50];
    
    // gets() is banned - extremely dangerous
    std::cout << "Enter some text: ";
    // gets(input_buffer);  // VULNERABLE: No bounds checking (commented to avoid crash)
    
    // Using scanf without width limit
    scanf("%s", input_buffer);  // VULNERABLE: No width specifier
    
    // Using strcpy, strcat without bounds checking
    strcpy(output_buffer, input_buffer);   // VULNERABLE
    strcat(output_buffer, " - processed");  // VULNERABLE
    
    // sprintf without size checking
    char final_buffer[30];
    sprintf(final_buffer, "Result: %s", output_buffer);  // VULNERABLE
    /* END VULNERABILITY */
    
    std::cout << "[DEBUG] Input processed\n";
}

// CWE-805: Buffer Access with Incorrect Length Value
void BufferOverflowVulns::incorrect_buffer_length(const char* src, int wrong_length) {
    std::cout << "[BufferOverflowVulns::incorrect_buffer_length]\n";
    
    /* START VULNERABILITY - CWE-805: Incorrect Buffer Length */
    char dest[32];
    
    // Using wrong length value
    memcpy(dest, src, wrong_length);  // VULNERABLE: wrong_length not validated
    
    // Another example with strncat using incorrect length
    char buffer[40] = "Prefix: ";
    strncat(buffer, src, wrong_length);  // VULNERABLE: length not checked against dest size
    /* END VULNERABILITY */
    
    std::cout << "[DEBUG] Buffer operation complete\n";
}

// ============================================================================
// CWE-190/191/680: Integer Overflow Vulnerabilities
// ============================================================================

// CWE-190: Integer Overflow
int IntegerVulns::integer_overflow_add(int a, int b) {
    std::cout << "[IntegerVulns::integer_overflow_add]\n";
    /* START VULNERABILITY - CWE-190: Integer Overflow */
    int result = a + b;  // VULNERABLE: No overflow check
    /* END VULNERABILITY */
    std::cout << "[DEBUG] Result: " << result << "\n";
    return result;
}

// CWE-191: Integer Underflow
unsigned int IntegerVulns::integer_underflow(unsigned int a, unsigned int b) {
    std::cout << "[IntegerVulns::integer_underflow]\n";
    /* START VULNERABILITY - CWE-191: Integer Underflow */
    unsigned int result = a - b;  // VULNERABLE: Can wrap around
    /* END VULNERABILITY */
    std::cout << "[DEBUG] Result: " << result << "\n";
    return result;
}

// CWE-680: Integer Overflow to Buffer Overflow
void IntegerVulns::integer_to_buffer_overflow(int size) {
    std::cout << "[IntegerVulns::integer_to_buffer_overflow]\n";
    /* START VULNERABILITY - CWE-680: Integer overflow leads to buffer overflow */
    int buffer_size = size + 100;  // VULNERABLE: size could overflow
    char* buffer = (char*)malloc(buffer_size);
    if (buffer) {
        memset(buffer, 'A', size);  // VULNERABLE: Uses original size, not checked
        free(buffer);
    }
    /* END VULNERABILITY */
}

// CWE-194: Sign Extension Error
void IntegerVulns::sign_extension_error(short value) {
    std::cout << "[IntegerVulns::sign_extension_error]\n";
    /* START VULNERABILITY - CWE-194: Unexpected Sign Extension */
    int extended = value;  // VULNERABLE: Negative short extends to negative int
    char buffer[100];
    memset(buffer, 0, extended);  // VULNERABLE: Negative value causes issues
    /* END VULNERABILITY */
}

// CWE-195: Signed to Unsigned Conversion
void IntegerVulns::signed_to_unsigned_error(int signed_value) {
    std::cout << "[IntegerVulns::signed_to_unsigned_error]\n";
    /* START VULNERABILITY - CWE-195: Signed to Unsigned Error */
    unsigned int size = signed_value;  // VULNERABLE: Negative becomes huge positive
    char* buffer = (char*)malloc(size);  // VULNERABLE: Huge allocation
    if (buffer) free(buffer);
    /* END VULNERABILITY */
}

// ============================================================================
// CWE-415/416/401: Memory Management Vulnerabilities
// ============================================================================

// CWE-415: Double Free
void MemoryVulns::double_free_vulnerability(char* ptr) {
    std::cout << "[MemoryVulns::double_free_vulnerability]\n";
    /* START VULNERABILITY - CWE-415: Double Free */
    free(ptr);
    // ... some code ...
    free(ptr);  // VULNERABLE: Freeing same pointer twice
    /* END VULNERABILITY */
}

// CWE-416: Use After Free
void MemoryVulns::use_after_free_vulnerability() {
    std::cout << "[MemoryVulns::use_after_free_vulnerability]\n";
    /* START VULNERABILITY - CWE-416: Use After Free */
    char* ptr = (char*)malloc(100);
    strcpy(ptr, "test data");
    free(ptr);
    // ... some code ...
    std::cout << "[DEBUG] Data: " << ptr << "\n";  // VULNERABLE: Using freed memory
    strcpy(ptr, "new data");  // VULNERABLE: Writing to freed memory
    /* END VULNERABILITY */
}

// CWE-401: Memory Leak
void MemoryVulns::memory_leak() {
    std::cout << "[MemoryVulns::memory_leak]\n";
    /* START VULNERABILITY - CWE-401: Memory Leak */
    char* leaked = (char*)malloc(1000);
    strcpy(leaked, "This memory is never freed");
    // VULNERABLE: No free() call - memory leaked
    /* END VULNERABILITY */
}

// CWE-404: Resource Leak
void MemoryVulns::resource_leak() {
    std::cout << "[MemoryVulns::resource_leak]\n";
    /* START VULNERABILITY - CWE-404: Resource Leak */
    FILE* file = fopen("/tmp/test.txt", "w");
    if (file) {
        fprintf(file, "test data");
        // VULNERABLE: File never closed
    }
    /* END VULNERABILITY */
}

// CWE-789: Uncontrolled Memory Allocation
void MemoryVulns::uncontrolled_memory_allocation(int user_size) {
    std::cout << "[MemoryVulns::uncontrolled_memory_allocation]\n";
    /* START VULNERABILITY - CWE-789: Uncontrolled Allocation */
    char* buffer = (char*)malloc(user_size);  // VULNERABLE: No size validation
    if (buffer) {
        memset(buffer, 0, user_size);
        free(buffer);
    }
    /* END VULNERABILITY */
}

// ============================================================================
// CWE-476/690: Null Pointer Vulnerabilities
// ============================================================================

// CWE-476: NULL Pointer Dereference
void NullPointerVulns::null_pointer_dereference(char* ptr) {
    std::cout << "[NullPointerVulns::null_pointer_dereference]\n";
    /* START VULNERABILITY - CWE-476: NULL Pointer Dereference */
    strcpy(ptr, "data");  // VULNERABLE: No NULL check
    std::cout << "[DEBUG] Data: " << ptr << "\n";
    /* END VULNERABILITY */
}

// CWE-690: Unchecked Return Value to NULL Pointer
void NullPointerVulns::unchecked_return_value() {
    std::cout << "[NullPointerVulns::unchecked_return_value]\n";
    /* START VULNERABILITY - CWE-690: Unchecked Return Value */
    char* ptr = (char*)malloc(100);
    // VULNERABLE: No check if malloc returned NULL
    strcpy(ptr, "test data");
    std::cout << "[DEBUG] Data: " << ptr << "\n";
    free(ptr);
    /* END VULNERABILITY */
}

// ============================================================================
// CWE-362/367: Race Condition Vulnerabilities
// ============================================================================

// CWE-362: Race Condition
void RaceConditionVulns::race_condition_file() {
    std::cout << "[RaceConditionVulns::race_condition_file]\n";
    /* START VULNERABILITY - CWE-362: Race Condition */
    const char* filename = "/tmp/shared_file.txt";
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        // VULNERABLE: File state can change between check and use
        file = fopen(filename, "w");  // Another process might have modified it
        if (file) {
            fprintf(file, "data");
            fclose(file);
        }
    }
    /* END VULNERABILITY */
}

// CWE-367: TOCTOU (Time-of-check Time-of-use)
void RaceConditionVulns::toctou_vulnerability(const char* filename) {
    std::cout << "[RaceConditionVulns::toctou_vulnerability]\n";
    /* START VULNERABILITY - CWE-367: TOCTOU */
    if (access(filename, F_OK) == 0) {  // Check if file exists
        // VULNERABLE: File state can change between check and open
        FILE* file = fopen(filename, "r");  // Use the file
        if (file) {
            char buffer[100];
            fgets(buffer, 100, file);
            fclose(file);
        }
    }
    /* END VULNERABILITY */
}

// ============================================================================
// CWE-457/665: Uninitialized Variable Vulnerabilities
// ============================================================================

// CWE-457: Use of Uninitialized Variable
int UninitializedVulns::use_uninitialized_variable() {
    std::cout << "[UninitializedVulns::use_uninitialized_variable]\n";
    /* START VULNERABILITY - CWE-457: Uninitialized Variable */
    int uninitialized;
    int result = uninitialized + 10;  // VULNERABLE: Using uninitialized variable
    /* END VULNERABILITY */
    std::cout << "[DEBUG] Result: " << result << "\n";
    return result;
}

// CWE-665: Improper Initialization
void UninitializedVulns::improper_initialization() {
    std::cout << "[UninitializedVulns::improper_initialization]\n";
    /* START VULNERABILITY - CWE-665: Improper Initialization */
    char buffer[100];
    // VULNERABLE: Buffer not initialized before use
    std::cout << "[DEBUG] Buffer contents: " << buffer << "\n";
    /* END VULNERABILITY */
}

// ============================================================================
// CWE-704/843: Type Confusion Vulnerabilities
// ============================================================================

// CWE-704: Incorrect Type Cast
void TypeVulns::incorrect_type_cast() {
    std::cout << "[TypeVulns::incorrect_type_cast]\n";
    /* START VULNERABILITY - CWE-704: Incorrect Type Cast */
    int* int_ptr = (int*)malloc(sizeof(int));
    *int_ptr = 0x41424344;
    char* char_ptr = (char*)int_ptr;  // VULNERABLE: Incorrect cast
    std::cout << "[DEBUG] Value: " << *char_ptr << "\n";
    free(int_ptr);
    /* END VULNERABILITY */
}

// CWE-843: Type Confusion
void TypeVulns::type_confusion() {
    std::cout << "[TypeVulns::type_confusion]\n";
    /* START VULNERABILITY - CWE-843: Type Confusion */
    float f = 3.14159f;
    int* int_alias = (int*)&f;  // VULNERABLE: Type punning
    std::cout << "[DEBUG] Float as int: " << *int_alias << "\n";
    /* END VULNERABILITY */
}

// ============================================================================
// CWE-325/330: Cryptography Vulnerabilities
// ============================================================================

// CWE-325: Missing Cryptographic Step
void CryptoVulns::missing_crypto_step(const char* password) {
    std::cout << "[CryptoVulns::missing_crypto_step]\n";
    /* START VULNERABILITY - CWE-325: Missing Crypto Step */
    // VULNERABLE: Password stored without hashing
    FILE* file = fopen("/tmp/passwords.txt", "a");
    if (file) {
        fprintf(file, "Password: %s\n", password);  // Plain text storage!
        fclose(file);
    }
    /* END VULNERABILITY */
}

// CWE-330: Weak Random Number
int CryptoVulns::weak_random_number() {
    std::cout << "[CryptoVulns::weak_random_number]\n";
    /* START VULNERABILITY - CWE-330: Weak Random */
    srand(12345);  // VULNERABLE: Predictable seed
    int random = rand();  // VULNERABLE: rand() is not cryptographically secure
    /* END VULNERABILITY */
    std::cout << "[DEBUG] Random: " << random << "\n";
    return random;
}

// ============================================================================
// CWE-732/250: Permission/Privilege Vulnerabilities
// ============================================================================

// CWE-732: Incorrect Permissions
void PermissionVulns::insecure_file_permissions(const char* filename) {
    std::cout << "[PermissionVulns::insecure_file_permissions]\n";
    /* START VULNERABILITY - CWE-732: Insecure Permissions */
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "sensitive data");
        fclose(file);
    }
    #ifdef _WIN32
    chmod(filename, _S_IREAD | _S_IWRITE);  // VULNERABLE: Windows permissions
    #else
    chmod(filename, 0777);  // VULNERABLE: World-readable/writable (Unix)
    #endif
    /* END VULNERABILITY */
}

// CWE-250: Unnecessary Privileges
void PermissionVulns::unnecessary_privileges() {
    std::cout << "[PermissionVulns::unnecessary_privileges]\n";
    /* START VULNERABILITY - CWE-250: Unnecessary Privileges */
    // VULNERABLE: Running with elevated privileges unnecessarily
    system("whoami");  // Should drop privileges before executing
    /* END VULNERABILITY */
}

// ============================================================================
// CWE-606/467/482/571/783: Logic Error Vulnerabilities
// ============================================================================

// CWE-606: Unchecked Input for Loop Condition
void LogicErrorVulns::unchecked_loop_condition(int user_count) {
    std::cout << "[LogicErrorVulns::unchecked_loop_condition]\n";
    /* START VULNERABILITY - CWE-606: Unchecked Loop Condition */
    char buffer[100];
    // VULNERABLE: user_count not validated, could be negative or huge
    for (int i = 0; i < user_count; i++) {
        buffer[i] = 'A';  // Buffer overflow if user_count > 100
    }
    /* END VULNERABILITY */
    std::cout << "[DEBUG] Loop completed with count: " << user_count << "\n";
}

// CWE-467: Use of sizeof() on a Pointer Type
void LogicErrorVulns::sizeof_on_pointer(const char* str) {
    std::cout << "[LogicErrorVulns::sizeof_on_pointer]\n";
    /* START VULNERABILITY - CWE-467: sizeof on Pointer */
    char buffer[100];
    // VULNERABLE: sizeof(str) returns pointer size (8), not string length
    memset(buffer, 0, sizeof(str));  // Only clears 8 bytes!
    strncpy(buffer, str, sizeof(str));  // Only copies 8 bytes!
    /* END VULNERABILITY */
    std::cout << "[DEBUG] Buffer operations completed\n";
}

// CWE-482: Comparing instead of Assigning
void LogicErrorVulns::compare_instead_of_assign(int value) {
    std::cout << "[LogicErrorVulns::compare_instead_of_assign]\n";
    int status = 0;
    /* START VULNERABILITY - CWE-482: Compare vs Assign */
    if (value > 10) {
        status == 1;  // VULNERABLE: Comparison instead of assignment
    }
    /* END VULNERABILITY */
    std::cout << "[DEBUG] Status: " << status << "\n";
}

// CWE-571: Expression is Always True
void LogicErrorVulns::always_true_expression(unsigned int value) {
    std::cout << "[LogicErrorVulns::always_true_expression]\n";
    /* START VULNERABILITY - CWE-571: Always True */
    // VULNERABLE: Unsigned value can never be < 0
    if (value >= 0) {
        std::cout << "[DEBUG] This always executes\n";
    }
    
    // Another example
    if (value < 0) {  // VULNERABLE: Never true for unsigned
        std::cout << "[DEBUG] This never executes\n";
    }
    /* END VULNERABILITY */
}

// CWE-783: Operator Precedence Logic Error
int LogicErrorVulns::operator_precedence_error(int flags) {
    std::cout << "[LogicErrorVulns::operator_precedence_error]\n";
    /* START VULNERABILITY - CWE-783: Precedence Error */
    int FLAG_READ = 1;
    int FLAG_WRITE = 2;
    int FLAG_EXECUTE = 4;
    
    // VULNERABLE: Bitwise & has lower precedence than ==
    // This evaluates as: flags & (FLAG_READ == FLAG_WRITE)
    if (flags & FLAG_READ == FLAG_WRITE) {
        std::cout << "[DEBUG] Unexpected logic due to precedence\n";
    }
    
    // VULNERABLE: Should be (flags & FLAG_EXECUTE) != 0
    if (flags & FLAG_EXECUTE) {  // Works but error-prone
        std::cout << "[DEBUG] Execute flag check\n";
    }
    /* END VULNERABILITY */
    return flags;
}

// ============================================================================
// CWE-242: Use of Inherently Dangerous Function
// ============================================================================

// CWE-242: Dangerous functions
void DangerousFunctionVulns::use_dangerous_functions() {
    std::cout << "[DangerousFunctionVulns::use_dangerous_functions]\n";
    /* START VULNERABILITY - CWE-242: Dangerous Functions */
    
    // VULNERABLE: tmpnam is unsafe (race condition)
    char temp_file[L_tmpnam];
    tmpnam(temp_file);
    std::cout << "[DEBUG] Temp file: " << temp_file << "\n";
    
    #ifndef _WIN32
    // VULNERABLE: mktemp is deprecated and unsafe (Unix only)
    char template_name[] = "/tmp/fileXXXXXX";
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    mktemp(template_name);
    #pragma GCC diagnostic pop
    std::cout << "[DEBUG] Template: " << template_name << "\n";
    
    // VULNERABLE: getwd is deprecated (buffer overflow risk) (Unix only)
    char cwd_old[1024];
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    getwd(cwd_old);  // Should use getcwd instead
    #pragma GCC diagnostic pop
    std::cout << "[DEBUG] Current dir (getwd): " << cwd_old << "\n";
    #endif
    
    // VULNERABLE: getcwd without error checking (cross-platform)
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));  // Should check for NULL return
    std::cout << "[DEBUG] Current dir: " << cwd << "\n";
    
    /* END VULNERABILITY */
}

// CWE-242: Dangerous signal handling
void signal_handler(int sig) {
    // VULNERABLE: Using printf in signal handler (non-async-signal-safe)
    printf("Signal %d received\n", sig);
    // VULNERABLE: Calling exit() in signal handler
    exit(1);
}

void DangerousFunctionVulns::dangerous_signal_handler() {
    std::cout << "[DangerousFunctionVulns::dangerous_signal_handler]\n";
    /* START VULNERABILITY - CWE-242: Dangerous Signal Handler */
    // VULNERABLE: signal() is obsolete, use sigaction()
    signal(SIGTERM, signal_handler);
    /* END VULNERABILITY */
    std::cout << "[DEBUG] Signal handler registered\n";
}

// ============================================================================
// CWE-561: Dead Code
// ============================================================================

// CWE-561: Unreachable code
void DeadCodeVulns::unreachable_code_example() {
    std::cout << "[DeadCodeVulns::unreachable_code_example]\n";
    /* START VULNERABILITY - CWE-561: Unreachable Code */
    
    int status = 0;
    return;  // Early return
    
    // VULNERABLE: This code is never executed
    status = 1;
    std::cout << "[DEBUG] Status updated: " << status << "\n";
    
    if (status > 0) {
        std::cout << "[DEBUG] Processing status\n";
    }
    /* END VULNERABILITY */
}

// CWE-561: Code after return
int DeadCodeVulns::code_after_return() {
    std::cout << "[DeadCodeVulns::code_after_return]\n";
    /* START VULNERABILITY - CWE-561: Dead Code After Return */
    
    int result = 42;
    return result;
    
    // VULNERABLE: Dead code - never executed
    result = 100;
    std::cout << "[DEBUG] This never prints\n";
    
    if (result > 50) {
        return result * 2;
    }
    
    return 0;
    /* END VULNERABILITY */
}

// Helper functions
std::string execute_sql_query(const std::string& query) {
    std::cout << "[SQL EXECUTION]\n";
    return (query.find("SELECT") != std::string::npos) ? "result_data" : "";
}

std::string execute_command(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) return "[ERROR] Command failed\n";
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
