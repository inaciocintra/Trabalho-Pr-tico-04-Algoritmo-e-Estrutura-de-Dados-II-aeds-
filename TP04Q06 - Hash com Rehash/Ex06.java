import java.util.Date;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

class Personagem {
    
    //-----atributos personagem-----
    private String id;
    private String name;
    private ArrayList<String> alternate_names;
    private String house;
    private String ancestry;
    private String species;
    private String patronus;
    private Boolean hogwartsStaff;
    private Boolean hogwartsStudent;
    private String actorName;
    private Boolean alive;
    private Date dateOfBirth;
    private int yearOfBirth;
    private String eyeColour;
    private String gender;
    private String hairColour;
    private Boolean wizard;
    private SimpleDateFormat formatodedata = new SimpleDateFormat("dd-MM-yyyy");

    //-----contrutor sem parametros-----
    public Personagem(){
        this.id = null;
        this.name = null;
        this.alternate_names = new ArrayList<String>();
        this.house = null;
        this.ancestry = null;
        this.species = null;
        this.patronus = null;
        this.hogwartsStaff = false;
        this.hogwartsStudent = null;
        this.actorName = null;
        this.alive = false;
        this.dateOfBirth = null;
        this.yearOfBirth = 0;
        this.eyeColour = null;
        this.gender = null;
        this.hairColour = null;
        this.wizard = false;

    }
    //-----construtor-----
    public Personagem(String id,String name,ArrayList<String> alternate_names,String house,String ancestry,String species,String patronus,Boolean hogwartsStaff,Boolean hogwartsStudent,String actorName,Boolean alive,Date dateOfBirth,int yearOfBirth,String eyeColour,String gender,String hairColour,Boolean wizard){
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
        this.dateOfBirth = dateOfBirth;
        this.yearOfBirth = yearOfBirth;
        this.eyeColour = eyeColour;
        this.gender = gender;
        this.hairColour = hairColour;
        this.wizard = wizard;
    }
    
    //-----métodos gets e sets-----

    public String getId(){
        return id;
    }
    public void setId(String id){
        this.id = id;
    }


    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name = name;
    }


    public ArrayList<String> getList(){

        return alternate_names;
    }
    public void setList(String todosapelidos){
        this.alternate_names.add(todosapelidos);
    }


    public String getHouse(){
        return house;
    }
    public void setHouse(String house){
        this.house = house;
    }


    public String getAncestry(){
        return ancestry;
    }
    public void setAncestry(String ancestry){
        this.ancestry = ancestry;
    }


    public String getSpecies(){
        return species;
    }
    public void setSpecies(String species){
        this.species = species;
    }


    public String getPatronus(){
        return patronus;
    }
    public void setPatronus(String patronus){
        this.patronus = patronus;
    }


    public Boolean getHogwartsStaff(){
        return hogwartsStaff;
    }
    public void setHogwartsStaff(String condicaostaff){
        this.hogwartsStaff = Boolean.parseBoolean(condicaostaff);
    }
    

    public Boolean getHogwartsStudent(){
        return hogwartsStudent;
    }
    public void setHogwartsStudent(String hogwartsStudent){
        this.hogwartsStudent = Boolean.parseBoolean(hogwartsStudent);
    }


    public String getActorName(){
        return actorName;
    }
    public void setActorName(String actorName){
        this.actorName = actorName;
    }


    public Boolean getAlive(){
        return alive;
    }
    public void setAlive(String vivo){
        this.alive = Boolean.parseBoolean(vivo);
    }


    public String getDate(){
        return formatodedata.format(dateOfBirth);
    }
    public void setDate(String dataoriginal){
        
        try {
            Date dataformatada = formatodedata.parse(dataoriginal);  // Convertendo a string para data
            this.dateOfBirth =  dataformatada;
        } catch (ParseException e) {
            System.out.println("Erro ao converter a data: " + e.getMessage());
        }
    }


    public int getYearOfBirth(){
        return yearOfBirth;
    }
    public void setYearOfBirth(int anoConvertido){
        this.yearOfBirth = anoConvertido;
        
    }


    public String getEyeColour(){
        return eyeColour;
    }
    public void setEyeColour(String eyeColour){
        this.eyeColour = eyeColour;
    }


    public String getGender(){
        return gender ;
    }
    public void setGender(String gender){
        this.gender = gender;
    }


    public String getHairColour(){
        return hairColour;
    }
    public void setHairColour(String hairColour ){
        this.hairColour = hairColour ;
    }


    public Boolean getWizard(){
        return wizard;
    }
    public void setWizard(String mago){
        this.wizard = Boolean.parseBoolean(mago);
    }
    
    //-----método clone-----
    public Personagem clone(){
        Personagem temp = new Personagem();
        temp.setYearOfBirth(this.yearOfBirth);
        temp.setName(this.name);
        return temp;
    }


    //-----método imprimir-----
    public void imprime(){
        System.out.print( "[" + getId() + " ## " + getName() + " ## ");
        System.out.print("{");
        for (int i = 0; i < alternate_names.size(); i++) {
        System.out.print(alternate_names.get(i));
        if (i < alternate_names.size() - 1) {
        System.out.print(", ");
        }
        }
        System.out.print("}");
        System.out.println(" ## " +getHouse()+ " ## " +getAncestry()+ " ## " + getSpecies()+ " ## " +getPatronus()+ " ## " +getHogwartsStaff() + " ## " +getHogwartsStudent() + " ## " +getActorName()+ " ## " +getAlive()+  " ## " +getDate()+ " ## " +getYearOfBirth()+ " ## " +getEyeColour()+ " ## " +getGender()+ " ## " +getHairColour()+ " ## " +getWizard()+ "]"); 
        
    } 





    //-----método ler-----
    //recebe  linha que vem da main
    public void ler(String linha){      
        //divide a linha ate cada ponto e virgula
        String[] dados = linha.split(";");
        if (dados.length >= 17) { 
            setId(dados[0]);
            setName(dados[1]) ; 
            //pega string dos apelidos e retira as chaves aspas e deixa somente os apelidos e a virgula
            String regex = "\\s+'|\\[|\\]|\\'";
        dados[2] = dados[2].replaceAll(regex, "");
        String[] temp = dados[2].split(",");
        for (int i = 0; i < temp.length; i++) {
            setList(temp[i]);
        }
            setHouse(dados[3]); 
            setAncestry(dados[4]);
            setSpecies(dados[5]);
            setPatronus(dados[6]);
            setHogwartsStaff(dados[7]);//alterar
            setHogwartsStudent(dados[8]);
            setActorName(dados[9]);
            setAlive(dados[10]);//alterar
            setDate(dados[12]);//alterar

            //alterando o ano de nascimento de string para int e chamando o set
            try {
                int anoConvertido = Integer.parseInt(dados[13]);
                   
                setYearOfBirth(anoConvertido);//set como o ano ja em inteiro
                   
               } catch (NumberFormatException e) {
                   System.out.println("Erro ao converter a string para inteiro: " + e.getMessage());
               }


            setEyeColour(dados[14]);
            setGender(dados[15]);
            setHairColour(dados[16]);
            setWizard(dados[17]);//alterar
            }

        }
    }


    class Hash {
        Personagem tabela[];
        int m;
        int comparacoes;
     
        public Hash() {
           this(21);
        }
     
        public Hash(int m) {
           this.m = m;
           comparacoes = 0;
           this.tabela = new Personagem[this.m];
           for (int i = 0; i < m; i++) {
              tabela[i] = null;
           }
           
        }

        //metodo de rehash c/ string
        public int rehash2(String codigo){
            
            int somaAscii = 0;
    
            for (int i = 0; i < codigo.length(); i++) {
                somaAscii += (int) codigo.charAt(i);
            }

           somaAscii += 1;
    
            return Math.abs(somaAscii) % m;
        }

        //metodo de hash c/string
        public int hash2(String codigo){
            int resultadoAscii = 0;
            for (int i = 0; i < codigo.length(); i++) {
                resultadoAscii += (int) codigo.charAt(i);
            }
            return Math.abs(resultadoAscii) % m;
        }

     
        public boolean inserir(Personagem personagem) {
           boolean resp = false;
           if (personagem != null) {
            comparacoes++;
              int pos = hash2(personagem.getName());
              if (tabela[pos] == null) {
                    comparacoes++;
                 tabela[pos] = personagem;
                 resp = true;
              } else {
                pos = rehash2(personagem.getName());
                if (tabela[pos] == null) {
                    tabela[pos] = personagem;
                    resp = true;
                 }
              }
           }
           return resp;
        }
     

        public boolean pesquisar(String codigo) {
        boolean resp = false;

        // Função hash para encontrar a posição inicial
        int pos = hash2(codigo);  
        if(tabela[pos] != null){  

            if (tabela[pos].getName().equals(codigo)){  
            comparacoes++;
            resp = true;
            System.out.print("(pos: " + pos + ") ");
            } 

        //se a pos tiver cheia da o rehash
        else{  

            int pos2=rehash2(codigo);       
            if(tabela[pos2] != null && tabela[pos2].getName().equals(codigo)){
            comparacoes++;
            System.out.print("(pos: " + pos2 + ") ");
            resp = true;}
            }
        }

        return resp;
    }   
}  
    



    


public class Ex06{
    public static void main(String[] args) {
        long startTime = System.nanoTime();
        Hash tabela = new Hash();
        FileReader filereader;
        BufferedReader reader;
        Scanner entrada = new Scanner(System.in);

        //codigo eh a string que vai ler o id e nomes
        String codigo;
        String nomeArquivo = "/tmp/characters.csv";
    
        try {

         
         codigo = entrada.nextLine();
         String linha;
         Boolean existe = true;
         
         //le a primeira linha csv e nao usa ela
         
         //enquanto o codigo da pub.in diferente de fim
         while(!(codigo.equals("FIM"))){
             filereader = new FileReader(nomeArquivo);
             reader = new BufferedReader(filereader);
             reader.readLine();
        //pega a linha csv
        while((linha = reader.readLine()) != null){
            
            //compara com a linha do csv
            for (int i = 0 ; i<32;i++){
                if(linha.charAt(i) != codigo.charAt(i)){
                    existe = false;
                    i =32;
                }
                else{
                    existe =true;
                }

            }

            //se o codigo/id existir no csv
            if (existe){
                //cria um personagem e chama o metodo ler da classe personagem passando a linha por parametro que irá setar os atributos
                Personagem personagem = new Personagem();
                personagem.ler(linha);
                //add o personagem no vetor
                try {
                    tabela.inserir(personagem);
                } catch (Exception e) {
                    
                   
                }
            }
            
        }
        filereader.close();
        reader.close();
        codigo = entrada.nextLine();
} 

        codigo = entrada.nextLine();
        while (!codigo.equals("FIM")) {
        System.out.print(codigo+ " ");
        if(tabela.pesquisar(codigo)) {
           
            System.out.println("SIM");
        }
        else{
            System.out.println("NAO");
        }
        codigo = entrada.nextLine();     
    }
}
catch(IOException e){ 
    

} 
long endTime = System.nanoTime(); 
long duration = (endTime - startTime) / 1000000; 
try (BufferedWriter writer = new BufferedWriter(new FileWriter("matrícula_hashRehash.txt"))) {
    writer.write("803040\t" + duration + "\t" + tabela.comparacoes + "\t"  );
} catch (IOException e) {
    System.err.println("Erro ao escrever no arquivo de log: " + e.getMessage());
}
entrada.close();
} 

} 