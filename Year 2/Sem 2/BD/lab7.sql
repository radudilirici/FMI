CREATE TABLE EMP_RDI AS SELECT * FROM employees;
CREATE TABLE DEPT_RDI AS SELECT * FROM departments;

-- 4
ALTER TABLE emp_rdi
ADD CONSTRAINT pk_emp_rdi PRIMARY KEY(employee_id);
ALTER TABLE dept_rdi
ADD CONSTRAINT pk_dept_rdi PRIMARY KEY(department_id);
ALTER TABLE emp_rdi
ADD CONSTRAINT fk_emp_dept_rdi
FOREIGN KEY(department_id) REFERENCES dept_rdi(department_id);

-- 5
INSERT INTO dept_rdi (department_id, department_name)
VALUES (300, 'Programare');
rollback;

desc dept_rdi;