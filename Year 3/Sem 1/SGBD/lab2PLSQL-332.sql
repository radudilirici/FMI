DECLARE
 x NUMBER(1) := 5;
 y x%TYPE := NULL;
BEGIN
 IF x <> y THEN
 DBMS_OUTPUT.PUT_LINE ('valoare <> null este = true');
 ELSE
 DBMS_OUTPUT.PUT_LINE ('valoare <> null este != true');
 END IF;

 x := NULL;
 IF x = y THEN
 DBMS_OUTPUT.PUT_LINE ('null = null este = true');
 ELSE
 DBMS_OUTPUT.PUT_LINE ('null = null este != true');
 END IF;
END;
/

--2
--a
DECLARE
 TYPE emp_record IS RECORD
 (cod employees.employee_id%TYPE,
 salariu employees.salary%TYPE,
 job employees.job_id%TYPE);
 v_ang emp_record;
BEGIN
 v_ang.cod:=700;
 v_ang.salariu:= 9000;
 v_ang.job:='SA_MAN';
 DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod ||
 ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
END;
/
--b
DECLARE
 TYPE emp_record IS RECORD
 (cod employees.employee_id%TYPE,
 salariu employees.salary%TYPE,
 job employees.job_id%TYPE);
 v_ang emp_record;
BEGIN
SELECT employee_id, salary, job_id
INTO v_ang
FROM employees
WHERE employee_id = 101;
DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod ||
 ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
END;
/

DECLARE
 TYPE emp_record IS RECORD
 (cod employees.employee_id%TYPE,
 salariu employees.salary%TYPE,
 job employees.job_id%TYPE);
 v_ang emp_record;
BEGIN
SELECT employee_id, salary, job_id
 INTO v_ang.cod, v_ang.salariu, v_ang.job
 FROM employees
 WHERE employee_id = 101;
DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod ||
 ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
END;
/

create table emp_mng2 as select * from employees;

DECLARE
 TYPE emp_record IS RECORD
 (cod employees.employee_id%TYPE,
 salariu employees.salary%TYPE,
 job employees.job_id%TYPE);
 v_ang emp_record;
BEGIN
DELETE FROM emp_mng2
WHERE employee_id=100
RETURNING employee_id, salary, job_id INTO v_ang;
DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod ||
 ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
END;
/

select * from emp_mng2  where employee_id =100;
ROLLBACK;

--3

DECLARE
v_ang1 employees%ROWTYPE;
v_ang2 employees%ROWTYPE;
BEGIN
-- sterg angajat 100 si mentin in variabila linia stearsa
 DELETE FROM emp_mng2
 WHERE employee_id = 100
 RETURNING employee_id, first_name, last_name, email, phone_number,
 hire_date, job_id, salary, commission_pct, manager_id,
 department_id
 INTO v_ang1;
-- inserez in tabel linia stearsa
 INSERT INTO emp_mng2
 VALUES v_ang1;
-- sterg angajat 101
 DELETE FROM emp_mng2
 WHERE employee_id = 101;
 -- obtin datele din tabelul employees
 SELECT *
 INTO v_ang2
 FROM employees
 WHERE employee_id = 101;
-- inserez o linie oarecare in emp_mng2
 INSERT INTO emp_mng2
 VALUES(1000,'FN','LN','E',null,sysdate, 'AD_VP',1000, null,100,90);
-- modific linia adaugata anterior cu valorile variabilei v_ang2
 UPDATE emp_mng2
 SET ROW = v_ang2
 WHERE employee_id = 1000;
END;
/
rollback;
select * from emp_mng2  where employee_id in (100, 101, 1000);



DECLARE
 TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
 t tablou_indexat;
BEGIN
-- punctul a
 FOR i IN 1..10 LOOP
 t(i):=i;
 END LOOP;
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(t(i) || ' ');
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul b
 FOR i IN 1..10 LOOP
       IF i mod 2 = 1 THEN t(i):=null;
       END IF;
 END LOOP;
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' ');
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
 
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(t(i) || ' ');
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul c
 t.DELETE(t.first);
 t.DELETE(5,7);
 t.DELETE(t.last);
 DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||
 ' si valoarea ' || nvl(t(t.first),0));
DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||
 ' si valoarea ' || nvl(t(t.last),0));
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 IF t.EXISTS(i) THEN
 DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' ');
 END IF;
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul d
 t.delete;
 DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/
--5
DECLARE
 TYPE tablou_indexat IS TABLE OF emp_mng2%ROWTYPE
 INDEX BY BINARY_INTEGER;
 t tablou_indexat;
BEGIN
-- stergere din tabel si salvare in tablou
 DELETE FROM emp_mng2
 WHERE ROWNUM<= 2
 RETURNING employee_id, first_name, last_name, email, phone_number,
 hire_date, job_id, salary, commission_pct, manager_id,
 department_id
 BULK COLLECT INTO t;
--afisare elemente tablou
 DBMS_OUTPUT.PUT_LINE (t(1).employee_id ||' ' || t(1).last_name);
 DBMS_OUTPUT.PUT_LINE (t(2).employee_id ||' ' || t(2).last_name);
--inserare cele 2 linii in tabel
 INSERT INTO emp_mng2 VALUES t(1);
 INSERT INTO emp_mng2 VALUES t(2);
 END;
/
select * from emp_mng2;

--6
DECLARE
 TYPE tablou_imbricat IS TABLE OF NUMBER;
 t tablou_imbricat := tablou_imbricat();
BEGIN
-- punctul a
 FOR i IN 1..10 LOOP
 t.extend;
 t(i):=i;
 END LOOP;
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');

 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(t(i) || ' ');
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
 -- punctul b
 FOR i IN 1..10 LOOP
 IF i mod 2 = 1 THEN t(i):=null;
 END IF;
 END LOOP;
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' ');
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul c
 t.DELETE(t.first);
 t.DELETE(5,7);
 t.DELETE(t.last);
 DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||
 ' si valoarea ' || nvl(t(t.first),0));
 DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||
 ' si valoarea ' || nvl(t(t.last),0));
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 IF t.EXISTS(i) THEN
 DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' ');
 END IF;
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul d
 t.delete;
 DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/

7. Declara?i un tip tablou imbricat de caractere ?i o variabil? de acest tip. Ini?ializa?i variabila cu
urm?toarele valori: m, i, n, i, m. Afi?a?i con?inutul tabloului, de la primul la ultimul element ?i
invers. ?terge?i elementele 2 ?i 4 ?i apoi afi?a?i con?inutul tabloului.
DECLARE
TYPE tablou_imbricat IS TABLE OF CHAR(1);
t tablou_imbricat := tablou_imbricat('m', 'i', 'n', 'i', 'm');
 i INTEGER;
BEGIN
i := t.FIRST;
WHILE i <= t.LAST LOOP
 DBMS_OUTPUT.PUT(t(i));
 i := t.NEXT(i);
END LOOP;
DBMS_OUTPUT.NEW_LINE;
 i := t.LAST;
WHILE i >= t.FIRST LOOP
 DBMS_OUTPUT.PUT(t(i));
 i := t.PRIOR(i);
  END LOOP;
DBMS_OUTPUT.NEW_LINE;
 t.delete(2);
 t.delete(4);
      i := t.FIRST;
      WHILE i <= t.LAST LOOP
       DBMS_OUTPUT.PUT(t(i));
       i := t.NEXT(i);
      END LOOP;
      DBMS_OUTPUT.NEW_LINE;
DBMS_OUTPUT.PUT_LINE('TEST');
       FOR i IN t.FIRST..t.LAST LOOP
       IF t.EXISTS(i) THEN
       DBMS_OUTPUT.PUT(nvl(t(i), 0));
       END IF;
       end loop;
       DBMS_OUTPUT.NEW_LINE;
 i := t.LAST;
WHILE i >= t.FIRST LOOP
 DBMS_OUTPUT.PUT(t(i));
 i := t.PRIOR(i);
END LOOP;
DBMS_OUTPUT.NEW_LINE;
END;
/

--8
DECLARE
 TYPE vector IS VARRAY(20) OF NUMBER;
 t vector:= vector();
BEGIN
-- punctul a
 FOR i IN 1..10 LOOP
 t.extend; t(i):=i;
 END LOOP;
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(t(i) || ' ');
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul b
 FOR i IN 1..10 LOOP
 IF i mod 2 = 1 THEN t(i):=null;
 END IF;
 END LOOP;
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' ');
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul c
-- metodele DELETE(n), DELETE(m,n) nu sunt valabile pentru vectori!!!
-- din vectori nu se pot sterge elemente individuale!!!
-- punctul d
 t.delete;
 DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/

9. Defini?i tipul subordonati_mng (vector, dimensiune maxim? 10, men?ine numere). Crea?i tabelul
manageri_mng cu urm?toarele câmpuri: cod_mgr NUMBER(10), nume VARCHAR2(20), lista
subordonati_mng. Introduce?i 3 linii în tabel. Afi?a?i informa?iile din tabel. ?terge?i tabelul creat,
apoi tipul.
CREATE OR REPLACE TYPE subordonati_mng AS VARRAY(10) OF NUMBER(4);
/
CREATE TABLE manageri_mng (cod_mgr NUMBER(10),
 nume VARCHAR2(20),
 lista subordonati_mng);
DECLARE
 v_sub subordonati_mng:= subordonati_mng(100,200,300);
 v_lista manageri_mng.lista%TYPE;
BEGIN
 INSERT INTO manageri_mng
 VALUES (1, 'Mgr 1', v_sub);
 INSERT INTO manageri_mng
 VALUES (2, 'Mgr 2', null);

 INSERT INTO manageri_mng
 VALUES (3, 'Mgr 3', subordonati_mng(400,500));

 SELECT lista
 INTO v_lista
 FROM manageri_mng
 WHERE cod_mgr=1;

 FOR j IN v_lista.FIRST..v_lista.LAST loop
 DBMS_OUTPUT.PUT_LINE (v_lista(j));
 END LOOP;
END;
/
SELECT * FROM manageri_mng;
DROP TABLE manageri_mng;
DROP TYPE subordonati_mng;

10. Crea?i tabelul emp_test_mng cu coloanele employee_id ?i last_name din tabelul employees.
Ad?uga?i în acest tabel un nou câmp numit telefon de tip tablou imbricat. Acest tablou va men?ine
pentru fiecare salariat toate numerele de telefon la care poate fi contactat. Insera?i o linie nou? în
tabel. Actualiza?i o linie din tabel. Afi?a?i informa?iile din tabel. ?terge?i tabelul ?i tipul.
CREATE TABLE emp_test_mng AS
 SELECT employee_id, last_name FROM employees
 WHERE ROWNUM <= 2;
 
 select * from emp_test_mng;
CREATE OR REPLACE TYPE tip_telefon_mng IS TABLE OF VARCHAR(12);
/
ALTER TABLE emp_test_mng
ADD (telefon tip_telefon_mng)
NESTED TABLE telefon STORE AS tabel_telefon_mng;


iNSERT INTO emp_test_mng
VALUES (500, 'XYZ',tip_telefon_mng('074XXX', '0213XXX', '037XXX'));

UPDATE emp_test_mng
SET telefon = tip_telefon_mng('073XXX', '0214XXX')
WHERE employee_id=100;

SELECT a.employee_id, b.*
FROM emp_test_mng a, TABLE (a.telefon) b;

500	074XXX
500	0213XXX
500	037XXX
100	073XXX
100	0214XXX

DROP TABLE emp_test_mng;
DROP TYPE tip_telefon_mng;

11. ?terge?i din tabelul emp_mng salaria?ii având codurile men?inute într-un vector.
Obs. Comanda FORALL permite ca toate liniile unei colec?ii s? fie transferate simultan printr-o
singur? opera?ie. Procedeul este numit bulk bind.
FORALL index IN lim_inf..lim_sup
 comanda_sql;
Varianta 1
DECLARE
 TYPE tip_cod IS VARRAY(5) OF NUMBER(3);
 coduri tip_cod := tip_cod(205,206);
BEGIN
 FOR i IN coduri.FIRST..coduri.LAST LOOP
 DELETE FROM emp_mng
 WHERE employee_id = coduri (i);
 END LOOP;
END;
/

create table emp_mng as select * from employees;
SELECT employee_id FROM emp_mng;
ROLLBACK;

Varianta 2
DECLARE
 TYPE tip_cod IS VARRAY(20) OF NUMBER;
 coduri tip_cod := tip_cod(205,206);
BEGIN
 FORALL i IN coduri.FIRST..coduri.LAST
 DELETE FROM emp_mng
 WHERE employee_id = coduri (i);
END;
/
SELECT employee_id FROM emp_mng;
ROLLBACK;


--ex
--1. Men?ine?i într-o colec?ie codurile celor mai prost pl?ti?i 5 angaja?i care nu câ?tig? comision. Folosind aceast?
--colec?ie m?ri?i cu 5% salariul acestor angaja?i. Afi?a?i valoarea veche a salariului, respectiv valoarea nou? a
--salariului. 

--nu
select employee_id, salary
from emp_mng
where commission_pct is null
and rownum<=5
order by salary;

104	6000
103	9000
101	17000
102	17000
100	24000

select employee_id
from (
select employee_id, salary
from emp_mng
where commission_pct is null
order by salary)
where rownum<=5;

132
128
136
127
135

declare
  type tip_cod is varray(5) of emp_mng.employee_id%type;
  coduri tip_cod;
  salariu emp_mng.salary%type;
begin
    select employee_id
    bulk collect into coduri
    from (
    select employee_id, salary
    from emp_mng
    where commission_pct is null
    order by salary)
    where rownum<=5;
    for i in  coduri.first..coduri.last loop
        select salary
        into salariu
        from emp_mng
        where employee_id = coduri(i);
        dbms_output.put_line('Angajatul cu codul ' || coduri(i) || ' are salariul vechi ' || salariu);
--        update emp_mng
--        set salary=salary*1.05
--        where employee_id = coduri(i);
--        select salary
--        into salariu
--        from emp_mng
--        where employee_id = coduri(i);
--        dbms_output.put_line('Angajatul cu codul ' || coduri(i) || ' are salariul nou ' || salariu);
--        dbms_output.new_line;
            
            update emp_mng
            set salary=salary*1.05
             where employee_id = coduri(i)
             returning salary into salariu;
             dbms_output.put_line('Angajatul cu codul ' || coduri(i) || ' are salariul nou ' || salariu);
      dbms_output.new_line;
    end loop;
  end;
  /
  rollback;
  
  declare
  type tip_cod is varray(5) of emp_mng.employee_id%type;
  coduri tip_cod;
  type tip_sal is varray(5) of emp_mng.salary%type;
  salariu tip_sal;
begin
    select employee_id, salary
    bulk collect into coduri, salariu
    from (
    select employee_id, salary
    from emp_mng
    where commission_pct is null
    order by salary)
    where rownum<=5;
    for i in  coduri.first..coduri.last loop
        dbms_output.put_line('Angajatul cu codul ' || coduri(i) || ' are salariul vechi ' || salariu(i));
      
    end loop;
    
    for i in coduri.first..coduri.last loop
          salariu(i) := salariu(i) * 1.05;
           update emp_mng set salary = salariu(i)
           where employee_id = coduri(i);
           dbms_output.put_line('Angajatul cu codul ' || coduri(i) || ' are salariul nou ' || salariu(i));
      end  loop;
  end;
  /
  
  commit;
   rollback;

Angajatul cu codul 132 are salariul vechi 2100
Angajatul cu codul 132 are salariul nou 2205

Angajatul cu codul 128 are salariul vechi 2200
Angajatul cu codul 128 are salariul nou 2310

Angajatul cu codul 136 are salariul vechi 2200
Angajatul cu codul 136 are salariul nou 2310

Angajatul cu codul 127 are salariul vechi 2400
Angajatul cu codul 127 are salariul nou 2520

Angajatul cu codul 135 are salariul vechi 2400
Angajatul cu codul 135 are salariul nou 2520


--2
create or replace type tip_orase_mng is table of varchar2(100);
/

create table excursie_mng(
cod_excursie number(4),
denumire varchar2(20),
status varchar2(20));


alter table excursie_mng
add (orase tip_orase_mng)
nested table  orase store as table_orase_mng;


insert into excursie_mng
values (0, 'Ex_0', 'disponibila', tip_orase_mng('oras1', 'oras2') );
select * from excursie_mng;


declare
 v_orase tip_orase_mng := tip_orase_mng('oras1', 'oras2' , 'oras3');
begin 
    for i in 1..5 loop
      insert into excursie_mng
      values (i, 'Excursie_' || i, 'disponibila', v_orase);
    end loop;
    end;
    /
    
    
0	Ex_0	disponibila	ANDREISUGEAC.TIP_ORASE_MNG('oras1','oras2')
1	Excursie_1	disponibila	ANDREISUGEAC.TIP_ORASE_MNG('oras1','oras2','oras3')
2	Excursie_2	disponibila	ANDREISUGEAC.TIP_ORASE_MNG('oras1','oras2','oras3')
3	Excursie_3	disponibila	ANDREISUGEAC.TIP_ORASE_MNG('oras1','oras2','oras3')
4	Excursie_4	disponibila	ANDREISUGEAC.TIP_ORASE_MNG('oras1','oras2','oras3')
5	Excursie_5	disponibila	ANDREISUGEAC.TIP_ORASE_MNG('oras1','oras2','oras3')
      
      
      Actualiza?i coloana orase pentru o excursie specificat?:
- ad?uga?i un ora? nou în list?, ce va fi ultimul vizitat în excursia respectiv?;

declare
  cod_exc excursie_mng.cod_excursie%type := &c_ex;
  v_orase tip_orase_mng;
  oras_t varchar2(20) :='Oras_nou';
begin
    select orase
    into v_orase
    from excursie_mng
    where cod_excursie= cod_exc;
--    for i in v_orase.first..v_orase.last loop
--        dbms_output.put_line( v_orase(i));
--    end loop;
    
    dbms_output.put_line(v_orase.last);
    v_orase.extend;
    dbms_output.put_line(v_orase.last);
    v_orase(v_orase.last) :=oras_t;
    update excursie_mng
    set orase = v_orase
    where cod_excursie= cod_exc;
    
end;

/
select * from excursie_mng;

      
