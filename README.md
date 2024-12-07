## 2.界面设计

### 2.1 登录界面

1. 用户输入账号、密码，
2. 用户点击"注册"后，发送账户密码到服务器，服务器检索数据库如果没有注册就添加进行，然后告知客户
3. 用户点击“登录”后发送账号、密码到服务器
4. 服务器接收到账号密码后，进行如下操作

   + 从数据库根据账号读取密码

   + 匹配两个密码，如果正确就设置成功状态码，并将个人账户数据和成功状态码发送到客户端

   + 如果密码不正确，发送失败状态码和空数据给客户

     

### 2.2 消息界面

#### **2.2.1私聊界面**

界面和功能：包括历史消息展示框、文本编辑框、表情包发送按钮、文件发送按钮、消息发送按钮



#### **2.2.2群聊界面**

界面：在私聊界面的基础上，要展示群成员和群主账号

功能：在私聊功能的基础上要添加上如果是群主可以删除群成员（群主身份验证）



#### **2.2.3 联系人界面**

界面：

1. 展示联系人分组
2. 展示联系人账号
3. 展示联系人昵称
4. 展示联系人头像

功能：

+ 删除好友

+ 添加好友

+ 点击好友，可跳转到私聊界面

  

## 3数据库设计

------
<center>表1：user_info</center>

| user_id | user_name | user_password | user_icon_base64 |
| ------- | --------- | ------------- | ---------------- |
|         |           |               |                  |
primary_key:(user_id);

涉及的功能
1. 注册
2. 修改密码
3. 修改名称
4. 上传图像

注：`user_icon_base64`为使用BASE64存储的字符串（如`data:image/png;base64,<SOME_BASE64>`）

------
<center>表2：group_info </center>

| group_id | group_name |
| -------- |  --------- |
|          |            |
primary_key:(group_id);
涉及的功能
1. 群聊创建
2. 群聊删除


------
<center>表3：user_friend</center>

| id   | user_id | friend_id |
| ---- | ------- | --------- |
|      |         |           |
primary_key:(user_id,friend_id);

涉及的功能
1. 添加好友
2. 删除好友


------
<center>表4：group_member</center>

| id   | group_id | member_id |
| ---- | -------- | --------- |
|      |          |           |
primary_key:(group_id,member_id);

涉及的功能
1. 邀请好友加入群聊
2. 将好友移出群聊

