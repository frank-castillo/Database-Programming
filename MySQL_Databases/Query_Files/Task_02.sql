create database task_02;
use task_02;

create table student(
	StudentName varchar(30),
    StudentNumber integer unsigned,
    Class integer unsigned,
    Major varchar(30),
    
    primary key (StudentNumber)
);

create table course(
	CourseName varchar(30),
    CourseNumber varchar(30),
    CreditHours smallint unsigned,
    Department varchar(30),
    
    primary key (CourseNumber)
);

create table section(
	SectionIdentifier integer unsigned,
    CourseNumber varchar(30),
    Semester varchar(30),
    sYear smallint unsigned,
    Instructor varchar(30),
    
    primary key (SectionIdentifier),
    foreign key (CourseNumber) references course (CourseNumber)
);

create table grade_report(
	StudentNumber integer unsigned,
    SectionIdentifier integer unsigned,
    Grade varchar(1),
    myIndex integer unsigned,
    
    primary key (myIndex),
    foreign key (StudentNumber) references student (StudentNumber),
    foreign key (SectionIdentifier) references section (SectionIdentifier)
);

create table prerequesite(
	CourseNumber varchar(30),
    PrerequesiteNumber varchar(30),
    myIndex integer unsigned,
    
    primary key (myIndex),
    foreign key (CourseNumber) references course (CourseNumber),
    foreign key (PrerequesiteNumber) references course (CourseNumber)
);