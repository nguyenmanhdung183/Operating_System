#!/bin/bash

# Hàm đệ quy để tìm file kích thước 0
function find_zero_size_files {
    local directory="$1"
    
    # Duyệt qua tất cả các file và thư mục con
    for item in "$directory"/*; do
        if [ -f "$item" ] && [ ! -s "$item" ]; then
            # Nếu là file và kích thước 0
            zero_size_files+=("$item")
        elif [ -d "$item" ]; then
            # Nếu là thư mục, gọi lại hàm đệ quy
            find_zero_size_files "$item"
        fi
    done
}

# Hàm đệ quy để xử lý các file và hỏi người dùng có muốn xóa không
function process_zero_size_files {
    for file in "${zero_size_files[@]}"; do
        ./t2   "Có" "Không" "$file"
        
        # Lấy kết quả từ chương trình C 
        choice=$?

        if [ $choice -eq 1 ]; then
            rm "$file"
            echo "$file đã bị xoá."
        else
            echo "$file không bị xoá."
        fi
    done
}

# Kiểm tra đầu vào
if [ $# -eq 0 ]; then
    echo "Cần cung cấp thư mục"
    exit 1
fi

directory="$1"

if [ ! -d "$directory" ]; then
    echo "$directory không phải là thư mục hợp lệ."
    exit 1
fi

# Khởi tạo mảng lưu các file kích thước 0
zero_size_files=()

# Tìm và in danh sách tất cả các file có kích thước 0
find_zero_size_files "$directory"

if [ ${#zero_size_files[@]} -eq 0 ]; then
    echo "Không có file nào có kích thước 0 trong thư mục $directory."
    exit 0
fi

# In danh sách tất cả các file
echo "Các file có kích thước 0 trong thư mục $directory:"
for file in "${zero_size_files[@]}"; do
    echo "$file"
done


# Xóa file 
process_zero_size_files
