
use smart_building_project;

SELECT 
    a.name AS a_id,
    atype.name AS a_type,
    l.floor AS a_floor,
    l.room AS a_room,
    a.log AS a_log,
    a.config AS config
FROM
    agent AS a
        JOIN
    agent_type AS atype ON a.type_id = atype.id
        JOIN
    location AS l ON a.location_id = l.id;


