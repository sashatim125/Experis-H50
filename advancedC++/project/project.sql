

CREATE SCHEMA `smart_building_project` ;

use smart_building_project;

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
	('ambient_temp','Temperature_Sensor_Simulator'),
    ('TestHVAC','HVAC_Controller_Simulator'),
    ('TestFire','Fire_Safety_Sensor_Simulator'),
    ('TestSprinkler','Sprinkler_Controller_Simulator');


insert into location (building, floor, room) values
	('main','1','room_1_a');


insert into agent(type_id, location_id, config) values
	(1,1,'units:F;lower:-5;upper:55;period:12'),
    (2,1,'iot:10.10.1.64;tmp77;shutdown:Fire_Detected|ROOM_EMPTY'),
    (3,1,'Fire_Detected;SIGUSER2'),
    (4,1,'On:Fire_Detected|Smoke_detected;iot:10.10.3.42');


ALTER TABLE agent 
ADD COLUMN `name` VARCHAR(64) not NULL AFTER `id`;

UPDATE agent
SET name = 'Temperature-1-a'
WHERE id = 1;

UPDATE agent
SET name = 'hvac-1-a'
WHERE id = 2;

UPDATE agent
SET name = 'fire-drill-test'
WHERE id = 3;

UPDATE agent
SET name = 'sprinkler-1-a'
WHERE id = 4;

ALTER TABLE agent 
ADD COLUMN `log` VARCHAR(64) not NULL AFTER `location_id`;


UPDATE agent
SET log = 'hvac_log'
WHERE id = 2;

UPDATE agent
SET log = 'safety'
WHERE id = 3;

UPDATE agent
SET log = 'safety'
WHERE id = 4;
