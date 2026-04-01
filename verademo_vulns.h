#ifndef VERADEMO_VULNS_H
#define VERADEMO_VULNS_H

#include <string>
#include <vector>

// Database simulation structure
struct User {
    std::string username;
    std::string password_hash;
    std::string real_name;
    std::string blab_name;
    std::string created_at;
};

struct Blab {
    int id;
    std::string username;
    std::string content;
    std::string timestamp;
    int comment_count;
};

// CWE-89: SQL Injection vulnerabilities
class UserController {
public:
    // CWE-89: SQL Injection in login (UserController.java line 138)
    static bool login_vulnerable(const std::string& username, const std::string& password);
    
    // CWE-89: SQL Injection in password hint (UserController.java line 239)
    static std::string get_password_hint_vulnerable(const std::string& username);
    
    // CWE-89: SQL Injection in registration (UserController.java line 332)
    static bool register_user_vulnerable(const std::string& username, 
                                         const std::string& password,
                                         const std::string& real_name,
                                         const std::string& blab_name);
    
    // CWE-89: SQL Injection in profile (UserController.java line 437)
    static std::vector<std::string> get_user_history_vulnerable(const std::string& username);
};

// CWE-78: OS Command Injection vulnerabilities
class ToolsController {
public:
    // CWE-78: Command Injection in ping (ToolsController.java line 39)
    static std::string ping_vulnerable(const std::string& host);
    
    // CWE-78: Command Injection in fortune (ToolsController.java line 58)
    static std::string fortune_vulnerable(const std::string& fortune_file);
};

// CWE-611: XML External Entity (XXE) vulnerability
class XMLParser {
public:
    // CWE-611: XXE vulnerability
    static std::string parse_xml_vulnerable(const std::string& xml_content);
};

// CWE-564: SQL Injection via ORDER BY clause
class BlabController {
public:
    // CWE-89 + CWE-564: SQL Injection in ORDER BY (BlabController.java line 335)
    static std::vector<User> get_blabbers_vulnerable(const std::string& username, 
                                                      const std::string& sort_column);
};

// CWE-327: Use of weak cryptographic algorithm (MD5)
class CryptoUtils {
public:
    // CWE-327: Weak crypto - MD5 for password hashing (UserController.java line 1095)
    static std::string md5_hash_vulnerable(const std::string& input);
};

// CWE-73: External Control of File Name or Path
class FileController {
public:
    // CWE-73: Path traversal in profile image download
    static std::string download_profile_image_vulnerable(const std::string& image_name);
};

// CWE-119/CWE-120/CWE-121/CWE-122: Buffer Overflow vulnerabilities
class BufferOverflowVulns {
public:
    // CWE-120: Buffer Copy without Checking Size of Input (strcpy)
    static void unsafe_string_copy(const char* user_input);
    
    // CWE-134: Uncontrolled Format String
    static void format_string_vulnerability(const char* user_input);
    
    // CWE-121: Stack-based Buffer Overflow
    static void stack_buffer_overflow(const char* user_data);
    
    // CWE-122: Heap-based Buffer Overflow
    static char* heap_buffer_overflow(const char* input);
    
    // CWE-126: Buffer Over-read
    static void buffer_overread(const char* data, int length);
    
    // CWE-676: Use of Potentially Dangerous Function (gets, sprintf)
    static void dangerous_function_usage();
    
    // CWE-805: Buffer Access with Incorrect Length Value
    static void incorrect_buffer_length(const char* src, int wrong_length);
};

// CWE-190/CWE-191/CWE-680: Integer Overflow vulnerabilities
class IntegerVulns {
public:
    // CWE-190: Integer Overflow or Wraparound
    static int integer_overflow_add(int a, int b);
    
    // CWE-191: Integer Underflow
    static unsigned int integer_underflow(unsigned int a, unsigned int b);
    
    // CWE-680: Integer Overflow to Buffer Overflow
    static void integer_to_buffer_overflow(int size);
    
    // CWE-194: Unexpected Sign Extension
    static void sign_extension_error(short value);
    
    // CWE-195: Signed to Unsigned Conversion Error
    static void signed_to_unsigned_error(int signed_value);
};

// CWE-415/CWE-416/CWE-401: Memory Management vulnerabilities
class MemoryVulns {
public:
    // CWE-415: Double Free
    static void double_free_vulnerability(char* ptr);
    
    // CWE-416: Use After Free
    static void use_after_free_vulnerability();
    
    // CWE-401: Missing Release of Memory after Effective Lifetime (Memory Leak)
    static void memory_leak();
    
    // CWE-404: Improper Resource Shutdown or Release
    static void resource_leak();
    
    // CWE-789: Uncontrolled Memory Allocation
    static void uncontrolled_memory_allocation(int user_size);
};

// CWE-476/CWE-690: Null Pointer Dereference vulnerabilities
class NullPointerVulns {
public:
    // CWE-476: NULL Pointer Dereference
    static void null_pointer_dereference(char* ptr);
    
    // CWE-690: Unchecked Return Value to NULL Pointer Dereference
    static void unchecked_return_value();
};

// CWE-362/CWE-367: Race Condition vulnerabilities
class RaceConditionVulns {
public:
    // CWE-362: Concurrent Execution using Shared Resource (Race Condition)
    static void race_condition_file();
    
    // CWE-367: Time-of-check Time-of-use (TOCTOU) Race Condition
    static void toctou_vulnerability(const char* filename);
};

// CWE-457/CWE-665: Uninitialized Variable vulnerabilities
class UninitializedVulns {
public:
    // CWE-457: Use of Uninitialized Variable
    static int use_uninitialized_variable();
    
    // CWE-665: Improper Initialization
    static void improper_initialization();
};

// CWE-704/CWE-843: Type Confusion vulnerabilities
class TypeVulns {
public:
    // CWE-704: Incorrect Type Conversion or Cast
    static void incorrect_type_cast();
    
    // CWE-843: Access of Resource Using Incompatible Type
    static void type_confusion();
};

// CWE-325/CWE-330: Cryptography vulnerabilities
class CryptoVulns {
public:
    // CWE-325: Missing Required Cryptographic Step
    static void missing_crypto_step(const char* password);
    
    // CWE-330: Use of Insufficiently Random Values
    static int weak_random_number();
};

// CWE-732/CWE-276: Permission/Privilege vulnerabilities
class PermissionVulns {
public:
    // CWE-732: Incorrect Permission Assignment for Critical Resource
    static void insecure_file_permissions(const char* filename);
    
    // CWE-250: Execution with Unnecessary Privileges
    static void unnecessary_privileges();
};

// CWE-606/467/482/571/783: Logic Error vulnerabilities
class LogicErrorVulns {
public:
    // CWE-606: Unchecked Input for Loop Condition
    static void unchecked_loop_condition(int user_count);
    
    // CWE-467: Use of sizeof() on a Pointer Type
    static void sizeof_on_pointer(const char* str);
    
    // CWE-482: Comparing instead of Assigning
    static void compare_instead_of_assign(int value);
    
    // CWE-571: Expression is Always True
    static void always_true_expression(unsigned int value);
    
    // CWE-783: Operator Precedence Logic Error
    static int operator_precedence_error(int flags);
};

// CWE-242: Use of Inherently Dangerous Function
class DangerousFunctionVulns {
public:
    // CWE-242: Dangerous functions (tmpnam, mktemp, getpass)
    static void use_dangerous_functions();
    
    // CWE-242: Dangerous signal handling
    static void dangerous_signal_handler();
};

// CWE-561: Dead Code
class DeadCodeVulns {
public:
    // CWE-561: Dead Code that is never executed
    static void unreachable_code_example();
    
    // CWE-561: Dead code after return
    static int code_after_return();
};

// Helper function to simulate SQL execution
std::string execute_sql_query(const std::string& query);

// Helper function to simulate command execution
std::string execute_command(const std::string& command);

#endif // VERADEMO_VULNS_H
