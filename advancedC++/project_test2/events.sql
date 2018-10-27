select count(*) FROM smart_building_project_test.events;
select * FROM smart_building_project_test.events;


drop table smart_building_project_test.events;

CREATE TABLE smart_building_project_test.events (
    id INT(20) AUTO_INCREMENT,
    agent_id INT(20) NOT NULL,
    time TIMESTAMP NOT NULL,
    description VARCHAR(1024),
    PRIMARY KEY (id),
    FOREIGN KEY (agent_id)
        REFERENCES agent (id)
        ON DELETE CASCADE
);