-- Usage: mysql -uroot -pbitnami mysql < create_db.sql
-- please type chcp 65001 to change your windows console from cp949 to utf8 support (cp65001)

use mysql;

delete from user where User='madang' and Host='madang';
insert into user(User, Host, Password) values ('madang', 'localhost', password('madang'));
flush privileges; -- please don't forget to add the following command

drop database if exists bookstore;
create database bookstore;

grant all on bookstore.* to 'madang'@'localhost' identified by 'madang';
flush privileges;

select 'my databases are ' as '';
show databases;
select 'currently registered users are' as '';
select User, Host, Password from user where User='madang';
