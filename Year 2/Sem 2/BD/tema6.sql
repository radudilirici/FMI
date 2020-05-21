-- 2
select project_id from works_on
where employee_id in (
    select employee_id from job_history
    group by employee_id
    having count(employee_id) = 2)
group by project_id
having count(employee_id) = (
    select count(*) from (select employee_id from job_history
    group by employee_id
    having count(employee_id) = 2));

-- 3
select employee_id from employees
where employee_id in (
    select employee_id from job_history
    group by employee_id
    having count(employee_id) >= 2)
union
select employee_id from job_history
    group by employee_id
    having count(employee_id) >= 3;

-- 4
select c.country_id, count(e.employee_id) from countries c
join locations l on l.country_id = c.country_id
join departments d on d.location_id = l.location_id
join employees e on e.department_id = d.department_id
group by c.country_id;

-- 5
select employee_id, last_name from employees
where employee_id in(
    select employee_id from works_on
    where project_id in (select project_id from projects where delivery_date > deadline)
    group by employee_id, last_name
    having count(employee_id) >= 2);

-- 6
select e.employee_id, w.project_idfrom employees e
left join works_on w on e.employee_id = w.employee_id;

-- 7
select *
from employees
where department_id in (
    select department_id
    from employees
    where employee_id in (
        select project_manager from projects));
        
-- 8
select *
from employees
where department_id not in (
    select department_id
    from employees
    where employee_id in (
        select project_manager from projects));

-- 9
select department_id, avg(salary)
from employees e
group by department_id
having avg(salary) > &salariu;

-- 10
select *
from employees
where employee_id in (
    select project_manager
    from projects
    group by project_manager
    having count(project_manager) >= 2);

-- 11
select employee_id from works_on
where project_id in (
    select project_id
    from projects
    where project_manager = 102)
and project_id not in (
    select project_id
    from projects
    where project_manager != 102);

-- 12
--a)
select employee_id from works_on
where project_id in (
    select project_id from works_on w
    group by project_id, employee_id
    having employee_id = 200)
group by employee_id
having count(project_id) >= (
    select count(*) from (
        select count(project_id) from works_on
        group by project_id, employee_id
        having employee_id = 200));
--b)
select employee_id from works_on
where project_id in (
    select project_id from works_on w
    group by project_id, employee_id
    having employee_id = 200)
group by employee_id
having count(project_id) <= (
select count(*) from (
    select count(project_id) from works_on
    group by project_id, employee_id
    having employee_id = 200));

-- 13
select employee_id from works_on
where project_id in (
    select project_id from works_on w
    group by project_id, employee_id
    having employee_id = 200)
group by employee_id
having count(project_id) = (
select count(*) from (
    select count(project_id) from works_on
    group by project_id, employee_id
    having employee_id = 200));

-- 14
-- a)
select * from job_grades;
-- b)
select e.employee_id, e.last_name, e.first_name, e.salary, (select grade_level from job_grades where e.salary >= lowest_sal and e.salary <= highest_sal)
from employees e;