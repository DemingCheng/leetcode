import base64
f=open('/data/intern/cmd/leetcode/C++/image/虚函数表内存分布.png','rb') #二进制方式打开图文件
ls_f=base64.b64encode(f.read()) #读取文件内容，转换为base64编码
f.close()
print(ls_f)

# fh = open('base64.txt', 'w', encoding='utf-8')
# fh.write("虚函数表内存分布")
# fh.write(ls_f).decode('utf-8')

fh = open('./base64.txt', 'wb')
fh.write("虚函数表内存分布\n".encode('utf-8'))
fh.write(ls_f)

fh.close()