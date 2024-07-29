import java.util.*;
import java.io.IOException;
import java.io.FileReader;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;



 class Personagem {
    private String id;
    private String name;
    private List<String> alternate_names;
    private  String house;
    private String ancestry;
    private String species;
    private  String patronus;
    private  Boolean hogwartsStaff;
    private Boolean hogwartsStudent;
    private   String actorName;
    private  Boolean alive;
       Date dateOfBirth;
    private   int yearOfBirth;
    private  String eyeColour;
    private  String gender;
    private  String hairColour;
    SimpleDateFormat formato =new SimpleDateFormat("dd-MM-yyyy");
    private Boolean wizard;
    
    public Personagem() {

    }

    public Personagem(String id, String name, List<String> alternate_names, String house, String ancestry,
            String species, String patronus,
            Boolean hogwartsStaff, Boolean hogwartsStudent, String actorName, Boolean alive, String dateOfBirth,
            int yearOfBirth, String eyeColour, String gender, String hairColour, Boolean wizard) {
        this.id = id;
        this.name = name;
        this.alternate_names = alternate_names;
        this.house = house;
        this.ancestry = ancestry;
        this.species = species;
        this.patronus = patronus;
        this.hogwartsStaff = hogwartsStaff;
        this.hogwartsStudent = hogwartsStudent;
        this.actorName = actorName;
        this.alive = alive;
        setDateOfBirth(dateOfBirth);
        this.yearOfBirth = yearOfBirth;
        this.eyeColour = eyeColour;
        this.gender = gender;
        this.hairColour = hairColour;
        this.wizard = wizard;
    }

   
    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public List<String> getAlternateNames() {
        return alternate_names;
    }

    public String getHouse() {
        return house;
    }

    public String getAncestry() {
        return ancestry;
    }

    public String getSpecies() {
        return species;
    }

    public String getPatronus() {
        return patronus;
    }

    public Boolean isHogwartsStaff() {
        return hogwartsStaff;
    }

    public Boolean isHogwartsStudent() {
        return hogwartsStudent;
    }

    public String getActorName() {
        return actorName;
    }

    public Boolean getisAlive() {
        return alive;
    }

    public Date getDateOfBirth() {
        return dateOfBirth;
    }

    public int getYearOfBirth() {
        return yearOfBirth;
    }

    public String getEyeColour() {
        return eyeColour;
    }

    public String getGender() {
        return gender;
    }

    public String getHairColour() {
        return hairColour;
    }

    public Boolean isWizard() {
        return wizard;
    }

    
    public void setId(String id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAlternateNames(List<String> alternate_names) {
        this.alternate_names = alternate_names;
    }

    public void setHouse(String house) {
        this.house = house;
    }

    public void setAncestry(String ancestry) {
        this.ancestry = ancestry;
    }

    public void setSpecies(String species) {
        this.species = species;
    }

    public void setPatronus(String patronus) {
        this.patronus = patronus;
    }

    public void setHogwartsStaff(Boolean hogwartsStaff) {
        this.hogwartsStaff = hogwartsStaff;
    }

    public void setHogwartsStudent(Boolean hogwartsStudent) {
        this.hogwartsStudent = hogwartsStudent;
    }

    public void setActorName(String actorName) {
        this.actorName = actorName;
    }

    public void setAlive(Boolean alive) {
        this.alive = alive;
    }

    public void setDateOfBirth(String dateOfBirth) {
        try {
            this.dateOfBirth = formato.parse(dateOfBirth);
        } catch (ParseException e) {
            System.err.println(e);
        }
    }

    public void setYearOfBirth(int yearOfBirth) {
        this.yearOfBirth = yearOfBirth;
    }

    public void setEyeColour(String eyeColour) {
        this.eyeColour = eyeColour;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public void setHairColour(String hairColour) {
        this.hairColour = hairColour;
    }

    public void setWizard(Boolean wizard) {
        this.wizard = wizard;
    }
    
    public void ler(String linha) {
        String testes[] = linha.split("\\[");
        List<String> valoresTeste2 = new ArrayList<>();
        for (int i = 0; i < testes.length; i++) {
            String testes2[] = testes[i].split("]");
            for (int j = 0; j < testes2.length; j++) {
                valoresTeste2.add(testes2[j]);
            }
        }
        List<String> alternateNamesList = new ArrayList<>();
        String textosemaspas = valoresTeste2.get(1).replace("'", "");
        String listaNomes[] = textosemaspas.split(",");
        for (String nome : listaNomes) {
            alternateNamesList.add(nome.trim()); 
        }
        setAlternateNames(alternateNamesList);

        String idnome[] = valoresTeste2.get(0).split(";");


        String humanalive[] = valoresTeste2.get(2).split(";");
        for (int n = 0; n < humanalive.length; n++) {
            if (humanalive[n].equals("VERDADEIRO")) {
                humanalive[n] = "true";
            }
            else if(humanalive[n].equals("FALSO")) {
                humanalive[n] = "false";
        }
    }

        String datawizard[] = valoresTeste2.get(4).split(";");
        for (int m = 0; m < datawizard.length; m++) {
            if (datawizard[m].equals("VERDADEIRO")) {
                datawizard[m] = "true";
            }
            else if(datawizard[m].equals("FALSO")) {
                datawizard[m] = "false";
        }}

        setId(idnome[0]);
        setName(idnome[1]);
        setHouse(humanalive[1]);
        setAncestry(humanalive[2]);
        setSpecies(humanalive[3]);
        setPatronus(humanalive[4]);
        setHogwartsStaff(Boolean.parseBoolean(humanalive[5]));
        setHogwartsStudent(Boolean.parseBoolean(humanalive[6]));
        setActorName(humanalive[7]);
        setAlive(Boolean.parseBoolean(humanalive[8]));
        setDateOfBirth(datawizard[1]);
        setYearOfBirth(Integer.parseInt(datawizard[2]));
        setEyeColour(datawizard[3]);
        setGender(datawizard[4]);
        setHairColour(datawizard[5]);
        setWizard(Boolean.parseBoolean(datawizard[6]));
    }
  public void imprimir (){
    String alternateNamesString = "{";
    for (String alternateName : alternate_names) {
        alternateNamesString += alternateName + ", ";
    }
    
    if (alternate_names.size() > 0) {
        alternateNamesString = alternateNamesString.substring(0, alternateNamesString.length() - 2);
    }
    alternateNamesString += "}";
    System.out.println(id+" ## "+name+" ## "+alternateNamesString+" ## "+house+" ## "+ancestry+" ## "+species+" ## "+patronus+" ## "+hogwartsStaff+" ## "+hogwartsStudent+
   " ## "+actorName+" ## "+alive+" ## "+formato.format(dateOfBirth)+" ## "+yearOfBirth+" ## "+eyeColour+" ## "+gender+" ## "+hairColour+" ## "+wizard+"]");

}

}




class No{
    public int elemento;
    public No esq, dir;
    public No2 outro;

    public No(int elemento){
        this(elemento, null, null);
        this.outro = null;
    }

    public No(int elemento, No esq, No dir){
        this.elemento = elemento;
        this.esq = esq;
        this.dir = dir;
        this.outro = null;
    }
}

class No2{
    public Personagem elemento;
    public No2 dir, esq;

    public No2(Personagem elemento){
        this(elemento, null, null);
    }

    public No2(Personagem elemento, No2 esq, No2 dir){
        this.elemento = elemento;
        this.esq = esq;
    }
}

 class ArvoreArvore{
    private No raiz;
    public int comp = 0;


    //cria árvore com raiz nula
    public ArvoreArvore(){
    raiz = null;
    }



    public void inserir(int x) throws Exception {
    raiz = inserir(x, raiz);
    }



    private No inserir(int x, No i) throws Exception {
    if (i == null) {
        i = new No(x);

    } else if (x < i.elemento) {
        i.esq = inserir(x, i.esq);

    } else if (x > i.elemento) {
        i.dir = inserir(x, i.dir);

    } else {
        throw new Exception("Erro");
    }
    comp++;
    return i;
    }

    //inserir No2 -> percorre a arvore1 -> acha a posicao da primeira letra -> percorre a segunda ->insere nela
    public void inserir(Personagem x) throws Exception{
        if(raiz != null){
            inserir(x, raiz);
        }
        
    }

    public void inserir(Personagem x, No i) throws Exception {
            if (i == null) {
            throw new Exception("Erro!");

        } else if ((x.getYearOfBirth()) % 15 < i.elemento) {
            inserir(x, i.esq);

        } else if ((x.getYearOfBirth()) % 15 > i.elemento) {
            inserir(x, i.dir);

        } else {
            i.outro = inserir(x, i.outro);
        }
        comp++;
    }

    private No2 inserir(Personagem x, No2 i) throws Exception {
        if (i == null) {
        i = new No2(x);

    } 
    else if (x.getName().compareTo(i.elemento.getName()) < 0) {
        i.esq = inserir(x, i.esq);

    } 
    else if (x.getName().compareTo(i.elemento.getName()) > 0) {
        i.dir = inserir(x, i.dir);

    } 
    else {
        throw new Exception("Erro");
    }
        comp++;
        return i;
    }

    public boolean caminharPesquisa(String x){
        return caminharPesquisa(x, raiz);
    }
    public boolean caminharPesquisa(String x, No i) {
        if (i != null) {
            if (caminharPesquisa(x, i.outro)) {
                return true;
            }
            System.out.print(" ESQ");
            if (caminharPesquisa(x, i.esq)) {
               return true;
            }
            
            System.out.print(" DIR");
            return caminharPesquisa(x, i.dir);
        }
        return false;
    }
    
    public boolean caminharPesquisa(String x, No2 i) {
        if (i == null) {
            return false;
        }
    
        if (x.equals(i.elemento.getName())) {
            return true;
        }
    
        System.out.print("esq->");
        if (caminharPesquisa(x, i.esq)) {
            return true;
        }
    
        System.out.print("dir->");
        return caminharPesquisa(x, i.dir);
    }
}
 
  


  public class Ex02{

public static void main(String[] args) throws Exception{
    ArvoreArvore arvore= new ArvoreArvore();

    long startTime = System.nanoTime();

    List<Personagem> personagens=new ArrayList<>();

    Scanner entrada = new Scanner(System.in);
    
    
    String nomeArquivo = "/tmp/characters.csv";

    try {
        FileReader fileReader = new FileReader(nomeArquivo);
        BufferedReader bufferedReader = new BufferedReader(fileReader);

        String lelinha;
        
        bufferedReader.readLine();
        while ((lelinha = bufferedReader.readLine()) != null) {
            Personagem personagem = new Personagem();
            personagem.ler(lelinha);
            personagens.add(personagem);
        }

        bufferedReader.close(); 
    } catch (IOException e) {
        
    }
    
    arvore.inserir(7);
    arvore.inserir(3);
    arvore.inserir(11);
    arvore.inserir(1);
    arvore.inserir(5);
    arvore.inserir(9);
    arvore.inserir(13);
    arvore.inserir(0);
    arvore.inserir(2);
    arvore.inserir(4);
    arvore.inserir(6);
    arvore.inserir(8);
    arvore.inserir(10);
    arvore.inserir(12);
    arvore.inserir(14);


    String codigo=entrada.nextLine();
    while(!codigo.equals("FIM")){
        for(int u=0;u<personagens.size();u++){
            
        if(codigo.equals(personagens.get(u).getId())){
        try{
        arvore.inserir(personagens.get(u));
        }
        catch (Exception e) {
        }
        }
        }
        codigo = entrada.nextLine();
        
    }
        codigo = entrada.nextLine();
    
    while (!codigo.equals("FIM")) {
        
        System.out.print(codigo);
        System.out.print(" => raiz");
        if(arvore.caminharPesquisa(codigo)){
            System.out.println(" SIM");
        }
        else{
            System.out.println(" NAO");
        }
        codigo = entrada.nextLine(); 
    }



        
    
    

long endTime = System.nanoTime(); 
    long duration = (endTime - startTime) / 1000000; 
    try (BufferedWriter writer = new BufferedWriter(new FileWriter("matrícula_arvoreArvore.txt"))) {
        writer.write("803040\t" + duration + "\t" + arvore.comp + "\t"  );
    } catch (IOException e) {
        System.err.println("Erro ao escrever no arquivo de log: " + e.getMessage());
    }
    entrada.close();
    
}
       
    }