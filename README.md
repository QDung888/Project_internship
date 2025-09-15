# Project\_internship

Trang git quan ly code trang web dieu khien, giao dien dieu khien va code vi xu ly esp32 cho mo hinh den giao thong



**Tạo 1 dự án trên github (tạo 1 project trống trên github sau đó clone về bắt đầu làm)**



B1: Tạo 1 Repositories trên github để chứa code dự án

B2: Cài đặt git trên PC và clone Repositories trên github về git clone your\_link\_repo

B3: code

* git status: trang thai file
* git add . : them file
* git commit -m "your\_message" : tao noi dung commit
* git push origin main : day code len github



**Tạo 1 project local và đẩy lên github (dành cho project đã có sẵn đẩy lên github)**



B1: tạo 1 github repo

B2: git init : để tạo .git tại thư mục chứa project trong máy, theo dõi code trong project

B3: viết code

* git status 
* git add .
* git commit -m "your\_mesage"
* git remote add origin https://....(link đến repo github)
* git push origin master (nếu lỗi thì git push -u origin master)



**Tạo 1 nhánh mới để phát triển code**

B1: git checkout branch\_name : lúc này sẽ tạo ra 1 branch mới và đang ở vị trí của branch mới

B2: Viết code, git add . , git commit -m "your\_message", git push origin branch\_name : Như vậy là đã đẩy được code lên branch mới

* Muốn đổi sang nhánh main thì git checkout main
* Muốn gộp branch vào main thì vào github, nhấn compare \& pullrequest, chọn nhánh muốn gộp vào main, nhấn create pullrequest, nhấn merge pullrequest, nhấn confirm merge



