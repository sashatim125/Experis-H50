

CREATE SCHEMA `smart_building_project_test` ;

use smart_building_project_test;

CREATE TABLE agent_type (
    id INT(20) AUTO_INCREMENT,
    name VARCHAR(64) NOT NULL,
    description VARCHAR(1024),
    PRIMARY KEY (id)
);

CREATE TABLE location (
    id INT(20) AUTO_INCREMENT,
    building VARCHAR(64) NOT NULL,
    floor VARCHAR(64) NOT NULL,
    room VARCHAR(64) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE agent (
    id INT(20) AUTO_INCREMENT,
    type_id INT(20) NOT NULL,
    location_id INT(20) NOT NULL,
    config VARCHAR(128),
    PRIMARY KEY (id),
    FOREIGN KEY (type_id)
        REFERENCES agent_type (id)
        ON DELETE CASCADE,
    FOREIGN KEY (location_id)
        REFERENCES location (id)
        ON DELETE CASCADE
);

CREATE TABLE events (
    id INT(20) AUTO_INCREMENT,
    agent_id INT(20) NOT NULL,
    time TIMESTAMP NOT NULL,
    description VARCHAR(1024),
    PRIMARY KEY (id),
    FOREIGN KEY (agent_id)
        REFERENCES agent (id)
        ON DELETE CASCADE
);

insert into agent_type (name,description) values
	('test_agent','Simple test agent'),
    ('DBLog','logger o the DB');


insert into location (building, floor, room) values
	('main','1','1');


insert into agent(type_id, location_id, config) values
	(1,1,'1001'),
	(1,1,'2001'),
	(1,1,'3001'),
	(1,1,'4001'),
	(1,1,'5001'),
	(1,1,'6001'),
	(1,1,'7001'),
	(1,1,'8001'),
	(1,1,'9001'),
	(1,1,'10001'),
	(2,1,'tcp://127.0.0.1:3306,root,student');

ALTER TABLE agent 
ADD COLUMN `name` VARCHAR(64) not NULL AFTER `id`;

UPDATE agent
SET name = 'Test1'
WHERE id = 1;

UPDATE agent
SET name = 'Test2'
WHERE id = 2;

UPDATE agent
SET name = 'Test3'
WHERE id = 3;

UPDATE agent
SET name = 'Test4'
WHERE id = 4;

UPDATE agent
SET name = 'Test5'
WHERE id = 5;

UPDATE agent
SET name = 'Test6'
WHERE id = 6;

UPDATE agent
SET name = 'Test7'
WHERE id = 7;

UPDATE agent
SET name = 'Test8'
WHERE id = 8;


UPDATE agent
SET name = 'Test9'
WHERE id = 9;


UPDATE agent
SET name = 'Test10'
WHERE id = 10;

UPDATE agent
SET name = 'sql_dblog'
WHERE id = 11;

ALTER TABLE agent 
ADD COLUMN `log` VARCHAR(64) not NULL AFTER `location_id`;


