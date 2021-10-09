set serveroutput on;

select * from emp_dlr;

update emp_dlr
set salary = 0
where employee_id = -1;

-- 1
create or replace trigger trig1_dlr
before delete on dept_dlr
begin
    if user != upper('scott') then
        raise_application_error(-20001, 'tabelul nu poate fi actualizat decat de SCOTT');
    end if;
end;
/
drop trigger trig1_dlr;

-- 2
create or replace trigger trig2_dlr
before update on emp_dlr
for each row
begin
    if (:new.commission_pct > :old.commission_pct) and (:new.commission_pct > :new.salary) then
        raise_application_error(-20001, 'comision prea mare');
    end if;
end;
/
drop trigger trig2_dlr;

-- 3
create or replace trigger trig3_dlr
before insert on emp_dlr
for each row
declare
    nr number(5);
begin
    select count(*)
    into nr
    from emp_dlr
    where department_id = :new.department_id;
    if nr > 45 then
        dbms_output.put_line(nr);
        raise_application_error(-20001, 'prea multi anagajati in departamentul '|| :new.department_id);
    end if;
end;
/

create sequence sec_dlr
start with 108;

insert into emp_dlr (employee_id, last_name, department_id, email, hire_date, job_id)
values (sec_dlr.nextval, 'test', 50, 'wqedsa@dsa.com', sysdate, 'IT_PROG');

drop trigger trig3_dlr;