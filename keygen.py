import sys,argparse, pyperclip
from typing import List

def generate_regcode(username: str) -> str:

    if not username:
        return "INVALID"
    
    # First stage: simple hash
    hash_val = 0x12345678  # Initial seed
    
    for char in username:
        # Rotate left 5 bits
        hash_val = ((hash_val << 5) | (hash_val >> 27)) & 0xFFFFFFFF
        hash_val ^= ord(char)
        hash_val = (hash_val + ((ord(char) * 0x1F) ^ 0xABCDEF)) & 0xFFFFFFFF
    
    # Second stage: additional processing
    hash_val ^= 0xF0F0F0F0
    hash_val = (~hash_val) & 0xFFFFFFFF
    # Bit swap: (hash & 0x55555555) << 1 | (hash & 0xAAAAAAAA) >> 1
    hash_val = ((hash_val & 0x55555555) << 1) | ((hash_val & 0xAAAAAAAA) >> 1)
    hash_val &= 0xFFFFFFFF
    
    # Third stage: final transformation
    hash_val = (hash_val * 0x9E3779B9) & 0xFFFFFFFF
    hash_val ^= (hash_val >> 16)
    hash_val &= 0xFFFFFFFF
    
    # Generate part2
    hash_val2 = hash_val ^ 0x87654321
    
    # Convert to hex strings
    part1 = f"{hash_val:08X}"
    part2 = f"{hash_val2:08X}"
    
    # Format: XXXX-XXXX-XXXX-XXXX
    return f"{part1[:4]}-{part1[4:]}-{part2[:4]}-{part2[4:]}"

def validate_regcode(username: str, regcode: str) -> bool:

    # Clean the code
    clean_code = regcode.replace('-', '').upper()
    
    # Generate expected code
    expected = generate_regcode(username).replace('-', '').upper()
    
    return clean_code == expected

def print_banner():

    banner = r"""
╔══════════════════════════════════════════════════╗
║                CRACKMEREG KEYGEN                 ║
║                  Version 1.0                     ║
║                                                  ║
║    Reverse Engineering Challenge - Key Generator ║
╚══════════════════════════════════════════════════╝
    """
    print(banner)

def print_colored(text: str, color_code: int):
    
    print(f"\033[{color_code}m{text}\033[0m")

def print_success(text: str):
    
    print_colored(text, 32)  # 32 = green

def print_error(text: str):
    
    print_colored(text, 31)  # 31 = red

def print_info(text: str):
    
    print_colored(text, 36)  # 36 = cyan

def batch_generate(usernames: List[str]):
    
    print("\n" + "="*60)
    print_info("BATCH GENERATION RESULTS:")
    print("="*60)
    
    results = []
    max_username_len = max(len(u) for u in usernames) if usernames else 0
    
    for username in usernames:
        regcode = generate_regcode(username)
        results.append((username, regcode))
    
    # Print table header
    print(f"\n{'Username':<{max_username_len}} | {'Registration Code'}")
    print("-" * (max_username_len + 3 + 19))
    
    # Print results
    for username, regcode in results:
        print(f"{username:<{max_username_len}} | {regcode}")
    
    return results

    

def interactive_mode():
    """Interactive mode for single code generation."""
    print_banner()
    
    while True:
        print("\n" + "-"*50)
        print_info("INTERACTIVE MODE")
        print("-"*50)
        
        username = input("\nEnter username (or 'quit' to exit): ").strip()
        
        if username.lower() in ['quit', 'exit', 'q']:
            break
        
        if not username:
            print_error("Username cannot be empty!")
            continue
        
        # Generate code
        regcode = generate_regcode(username)
        
        print("\n" + "="*50)
        print_success("REGISTRATION CODE GENERATED:")
        print("="*50)
        print(f"\nUsername:      {username}")
        print(f"Reg Code:      {regcode}")
        
        # Verify it
        is_valid = validate_regcode(username, regcode)
        status = "✓ VALID" if is_valid else "✗ INVALID"
        color = 32 if is_valid else 31  # Green or red
        
        print(f"Validation:    \033[{color}m{status}\033[0m")
        
        # Copy to clipboard option
        copy_to_clipboard = input("\nCopy to clipboard? (y/n): ").strip().lower()
        if copy_to_clipboard == 'y':
            try:
                pyperclip.copy(regcode)
                print_success("Code copied to clipboard!")
            except ImportError:
                print_error("pyperclip not installed. Install with: pip install pyperclip")
        
        # Another code?
        another = input("\nGenerate another code? (y/n): ").strip().lower()
        if another != 'y':
            break


def main():
    parser = argparse.ArgumentParser(
        description="Keygen for CrackMeReg.exe",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
    Examples:
      %(prog)s -u test                    # Generate code for 'test'
      %(prog)s -u admin -u user           # Generate codes for multiple users
      %(prog)s --interactive              # Interactive mode
        """
    )
    
    parser.add_argument('-u', '--username', action='append', 
                        help='Username(s) to generate codes for')
    parser.add_argument('-i', '--interactive', action='store_true',
                        help='Run in interactive mode')
    # reverse lookup removed per user request
    
    args = parser.parse_args()
    
    # If no arguments, show help
    if len(sys.argv) == 1:
        parser.print_help()
        return
    
    # reverse lookup removed per user request

    # Interactive mode
    if args.interactive:
        interactive_mode()
        return
    # Collect usernames
    usernames = []
    
    # From command line arguments
    if args.username:
        usernames.extend(args.username)
    
    
    # Generate codes
    if usernames:
        print_banner()
        batch_generate(usernames)
    else:
        print_error("No usernames provided!")
        parser.print_help()

if __name__ == "__main__":
    main()