

USE assign2db;

SHOW TABLES;

-- Part 1 SQL Updates
SELECT * FROM nurse;
-- Update nurse

UPDATE nurse SET lastname='Cyrus' WHERE firstname='Miley';
UPDATE nurse, doctor, workingfor SET nurse.startdate=doctor.startdate
 WHERE workingfor.docid=doctor.docid AND doctor.lastname='Tanaka'
 AND workingfor.nurseid = nurse.nurseid;

-- show nurse table
SELECT * FROM nurse;

-- Part 2 SQL Inserts
SELECT * FROM doctor;
INSERT INTO doctor (docid, firstname, lastname, birthdate, startdate) VALUES 
 ('RAN12', 'Micheal', 'Scott','1978-01-14', '2023-10-10');
INSERT INTO patient (ohip, firstname, lastname, birthdate, weight, height, treatsdocid)
VALUES ('111111112', 'Dwight', 'Schrute', '1980-01-01', 72, 1.82, 'RAN12');

INSERT INTO workingfor (docid, nurseid, hours)
VALUES ('RAN12', 'AAA13', 50);
INSERT INTO nurse (nurseid, firstname, lastname, startdate, reporttonurseid)
VALUES ('AAA13', 'Mary','Steep', '2021-02-10', 'BBBB2');

-- show it worked
SELECT * FROM doctor WHERE docid = 'RAN12';
-- Show the new patient and their doctor
SELECT p.*, d.firstname as doctor_firstname, d.lastname as doctor_lastname
FROM patient p
JOIN doctor d ON p.treatsdocid = d.docid
WHERE p.ohip = '111111112';

-- Show the new nurse and who they report to
SELECT n1.firstname as nurse_name, n1.lastname as nurse_lastname,
       n2.firstname as supervisor_firstname, n2.lastname as supervisor_lastname
FROM nurse n1
LEFT JOIN nurse n2 ON n1.reporttonurseid = n2.nurseid
WHERE n1.nurseid = 'AAA13';

-- Show the working relationship between the new nurse and doctor
SELECT d.firstname as doctor_firstname, d.lastname as doctor_lastname,
       n.firstname as nurse_firstname, n.lastname as nurse_lastname,
       w.hours
FROM workingfor w
JOIN doctor d ON w.docid = d.docid
JOIN nurse n ON w.nurseid = n.nurseid
WHERE w.docid = 'RAN12' AND w.nurseid = 'AAA13';

-- Part 3 SQL Queries

-- Query 1 
SELECT lastname FROM patient;

-- Query 2
SELECT DISTINCT lastname FROM patient;

-- Query 3
SELECT * FROM doctor ORDER BY startdate;

-- Query 4
SELECT ohip, firstname, lastname, weight 
FROM patient 
WHERE weight >= 50 
ORDER BY weight;

-- Query 5
SELECT p.firstname, p.lastname
FROM patient p
JOIN doctor d ON p.treatsdocid = d.docid
WHERE d.lastname = 'Tanaka';

-- Query 6
SELECT d.firstname, d.lastname, p.firstname as patient_firstname, p.lastname as patient_lastname
FROM doctor d
LEFT JOIN patient p ON d.docid = p.treatsdocid;

-- Query 7
SELECT firstname, lastname
FROM doctor
WHERE docid NOT IN (SELECT treatsdocid FROM patient WHERE treatsdocid IS NOT NULL);

-- Query 8
SELECT AVG(hours) as average_hours
FROM workingfor;

-- Query 9
SELECT 
   n1.firstname AS "Nurse First Name",
   n1.lastname AS "Nurse Last Name",
   n2.firstname AS "Supervisor First Name",
   n2.lastname AS "Supervisor Last Name"
FROM nurse n1
LEFT JOIN nurse n2 ON n1.reporttonurseid = n2.nurseid;

-- Query 10
SELECT 
   n.firstname,
   n.lastname,
   SUM(w.hours) as total_hours,
   CONCAT('$', FORMAT(SUM(w.hours) * 30, 2)) AS "Total Pay"
FROM nurse n
LEFT JOIN workingfor w ON n.nurseid = w.nurseid
GROUP BY n.nurseid, n.firstname, n.lastname
ORDER BY SUM(w.hours) * 30 DESC;

-- Query 11
SELECT 
   p.firstname AS patient_firstname,
   p.lastname AS patient_lastname,
   n.firstname AS nurse_firstname,
   n.lastname AS nurse_lastname
FROM patient p
JOIN doctor d ON p.treatsdocid = d.docid
JOIN workingfor w ON d.docid = w.docid
JOIN nurse n ON w.nurseid = n.nurseid;

-- Query 12
SELECT 
   p.firstname AS patient_firstname,
   p.lastname AS patient_lastname,
   TIMESTAMPDIFF(YEAR, p.birthdate, CURDATE()) AS patient_age,
   p.birthdate AS patient_birthdate,
   d.firstname AS doctor_firstname,
   d.lastname AS doctor_lastname,
   TIMESTAMPDIFF(YEAR, d.birthdate, CURDATE()) AS doctor_age,
   d.birthdate AS doctor_birthdate
FROM patient p
JOIN doctor d ON p.treatsdocid = d.docid
WHERE p.birthdate < d.birthdate;

-- Query 13
SELECT DISTINCT n.firstname, n.lastname
FROM nurse n
WHERE n.nurseid NOT IN (
   SELECT w.nurseid 
   FROM workingfor w 
   JOIN doctor d ON w.docid = d.docid 
   WHERE d.lastname = 'Tanaka'
);

-- Query 14
SELECT 
   n.firstname,
   n.lastname,
   COUNT(w.docid) as number_of_doctors
FROM nurse n
JOIN workingfor w ON n.nurseid = w.nurseid
GROUP BY n.nurseid, n.firstname, n.lastname
HAVING COUNT(w.docid) > 1;

-- Query 15: Find nurses who work more hours than average and show how much more they work
SELECT 
   n.firstname,
   n.lastname,
   SUM(w.hours) as total_hours,
   (SELECT AVG(hours) FROM workingfor) as avg_hours,
   SUM(w.hours) - (SELECT AVG(hours) FROM workingfor) as hours_above_average
FROM nurse n
JOIN workingfor w ON n.nurseid = w.nurseid
GROUP BY n.nurseid, n.firstname, n.lastname
HAVING SUM(w.hours) > (SELECT AVG(hours) FROM workingfor)
ORDER BY hours_above_average DESC;


-- Part 4 SQL views/deletes
CREATE VIEW Doctor_Patient_Count AS
SELECT d.firstname, d.lastname, COUNT(p.ohip) AS numofpat
FROM doctor d
LEFT JOIN patient p ON d.docid = p.treatsdocid
GROUP BY d.docid, d.firstname, d.lastname
HAVING COUNT(p.ohip) > 0; 

SELECT *
FROM Doctor_Patient_Count
WHERE numofpat = 2;

SELECT *
FROM doctor;

DELETE FROM doctor
WHERE docid = 'HIT45';

SELECT *
FROM doctor
WHERE docid = 'HIT45';
-- return 0 rows if the doctor is deleted successfully

SELECT COUNT(*)
FROM doctor;

DELETE FROM doctor
WHERE docid = 'RAD34';


SELECT COUNT(*)
FROM doctor;
-- counter should be decreased if rad34 is deleted successfully
-- this is not deleted because RAD34 is a foreign key in the the patient table and since on delete is restricted it will not allow the row with the fk in the doctors table.
