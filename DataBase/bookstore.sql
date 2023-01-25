-- wampstack command prompt, mysql -umadang -pmadang bookstore < bookstore.sql

drop database bookstore;
create database bookstore;

use bookstore;

create table Book (
    bookid INT NOT NULL AUTO_INCREMENT,
    bookname VARCHAR(100) NOT NULL,
    publisher VARCHAR(50) NOT NULL,
    price INT,
    primary key (bookid)
);

insert into Book values (NULL,'축구의 역사','굿스포츠',7000);
insert into Book values (NULL,'축구 아는 여자','나무수',13000);
insert into Book values (NULL,'축구의 이해','대한미디어',22000);
insert into Book values (NULL,'골프 바이블','대한미디어',35000);
insert into Book values (NULL,'피겨 교본','굿스포츠',8000);
insert into Book values (NULL,'역도 단계별 기술','굿스포츠',6000);
insert into Book values (NULL,'야구의 주먹','이상미디어',20000);
insert into Book values (NULL,'야구를 부탁해','이상미디어',13000);
insert into Book values (NULL,'올림픽 이야기','삼성당',7500);
insert into Book values (NULL,'Olympic Champions','굿스포츠',13000);

select 'check' as '';
select * from Book;

create table Customer (
    custid INT NOT NULL AUTO_INCREMENT,
    name    VARCHAR(40) NOT NULL,
    address VARCHAR(100),
    phone   CHAR(13),
    primary key (custid)
);

insert into Customer values(NULL, '박지성', '영국 맨체스터', '000-5000-0001');
insert into Customer values(NULL, '김연아', '대한민국 과천', '000-6000-0001');
insert into Customer values(NULL, '장미란', '대한민국 태릉', '000-7000-0001');
insert into Customer values(NULL, '추신수', '미국 텍사스',  '000-8000-0001');
insert into Customer values(NULL, '박세리', '대한민국 대전', NULL);

select 'customer tuples' as '';
select * from Customer;

create table Orders (
    orderid INT NOT NULL AUTO_INCREMENT,
    custid INT NOT NULL,
    bookid INT NOT NULL,
    saleprice INT NOT NULL,
    orderdate DATETIME NOT NULL,
    primary key (orderid),
    foreign key (custid) references Customer(custid),
    foreign key (bookid) references Book(bookid)
);

insert into Orders values(NULL, 1, 1, 6000, '2013-07-01');
insert into Orders values(NULL, 1, 3, 21000, '2013-07-03');
insert into Orders values(NULL, 2, 5, 8000, '2013-07-03');
insert into Orders values(NULL, 3, 6, 6000, '2013-07-04');
insert into Orders values(NULL, 4, 7, 20000, '2013-07-05');
insert into Orders values(NULL, 1, 2, 12000, '2013-07-07');
insert into Orders values(NULL, 4, 8, 13000, '2013-07-07');
insert into Orders values(NULL, 3, 10, 12000, '2013-07-08');
insert into Orders values(NULL, 2, 10, 7000, '2013-07-09');
insert into Orders values(NULL, 3, 8, 13000, '2013-07-10');

select 'order tuples' as '';
select * from Orders;


select c.name , o.saleprices
from Customer c , Orders,c
where c.custid=o.custid;

select Customer.name, saleprice
from Customer LEFT OUTER JOIN 
     Oders ON Customer.custid=Orders.custid;

select Customer.name ,saleprice
from Customer INNER JOIN
     Oders
where Customer.custid=Oders.custid;


select bookname 
from Book
where price =(select MAX(price) from Book);

select bookname, MAX(price)
from Book
Order by price desc limit 1;

select MAX(price)
from book;

select name
from Customer
where Customer.custid in (select custid from Order);

select name
from Customer
where Customer.custid=Order.custid;

select name 
from Customer
where Custid in (select customer from Orders where bookid in (select bookid from book where publisher='대한미디어'));

select b1.bookname
from book b1
where b1.price > (select AVG(b2.price) from book b2 where b1.publisher=b2.publisher)

select b1.bookname
from book b1
where b1.price > (select AVG(b2.price) from book b2 group by publisher having b1.publisher=b2.publisher)
