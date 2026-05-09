from pathlib import Path

def main() -> None:
    count = 0
    empty_lines_count = 0
    output = []

    for path in Path('..').rglob('*'):
        if not path.is_file() or '__pycache__' in str(path) or ('.c' not in str(path) and '.h' not in str(path)) or 'ramfs_disk' in str(path):
            continue

        with open(path, 'r', encoding='utf-8') as file:
            content = file.read()
            output.append(str(path))
            output.append(content)

            lines = content.splitlines()
            count += len(lines)

            for line in lines:
                if not line:
                    empty_lines_count += 1
    
    print(f'[*] total project line count: {count}')
    print(f'[*] total empty lines count: {empty_lines_count}')
    print(f'[*] project line count - empty lines count = {count - empty_lines_count}')

    with open('loc_output.txt', 'w') as file:
        file.write('\n'.join(output))

if __name__ == '__main__':
    main()
