package asociere;

public class Main {

    public static void main(String[] args) {

        Profesor profMatePrincipal = new Profesor(1, "Popescu");
        Profesor profMateSecundar = new Profesor(2, "Ionescu");
        Profesor profInfo = new Profesor(3, "Anghel");
        Profesor profMateInfo = new Profesor(4, "Petrescu");
        Profesor profInfoMate = new Profesor(5, "Andrei");

        Departament depInfo = new Departament("info");
        depInfo.setProfesori(new Profesor[] {profInfo, profInfoMate, profMateInfo});
        Departament depMate = new Departament("mate");
        depMate.setProfesori(new Profesor[] {profMatePrincipal, profMateSecundar, profInfoMate, profMateInfo});

        Universitate unibuc = new Universitate("unibuc", new Departament[] {depInfo, depMate});

        System.out.println(unibuc);

        depInfo = null;
        System.out.println(unibuc);

        System.out.println(depMate);
        depMate.getProfesori()[1] = null;
        System.out.println(depMate);
        System.out.println(profMatePrincipal);

    }
}
