/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp;

import java.util.Iterator;
import java.util.Set;
import lp.HotelCachorros.*;
import lp.HotelCachorros.Persistencia.BancoDeDados;
import lp.HotelCachorros.Persistencia.CadastroException;

/*
 *
 * @author vanderson
 */

public class ControladorDeCadastro {

    public static void main(String args[]) {

        PorteFaixa f1 = new PorteFaixa(0d, 20d, 0d, 30d, Especie.Cachorro,
                Porte.Pequeno);
        PorteFaixa f2 = new PorteFaixa(21d, 40d, 31d, 60d, Especie.Cachorro,
                Porte.Medio);
        PorteFaixa f3 = new PorteFaixa(41d, 60d, 61d, 80d, Especie.Cachorro,
                Porte.Grande);
        BancoDeDados.getInstance().getPortesFaixas().add(f1);
        BancoDeDados.getInstance().getPortesFaixas().add(f2);
        BancoDeDados.getInstance().getPortesFaixas().add(f3);
        //cria instâncias de animal(ver o construtor na classe Animal
        
        Animal a1 = new Animal(null, null,
                Especie.Cachorro, 10d, 15d);
        Animal a2 = new Animal(null, null,
                Especie.Cachorro, 20d, 35d);
        Animal a3 = new Animal(null, null,
                Especie.Cachorro, 45d, 60d);
        Animal a4 = new Animal(null, null,
                Especie.Cachorro, 100d, 100d);
        
        ControladorDeCadastro c = new ControladorDeCadastro();
        try {
            System.out.println(c.classificarPorte(a1));
            System.out.println(c.classificarPorte(a2));
            System.out.println(c.classificarPorte(a3));
            System.out.println(c.classificarPorte(a4));
        } catch (CadastroException e) {
            e.printStackTrace();
        }


    }

    
    public String classificarPorte(Animal animal) throws CadastroException{
            Set<PorteFaixa> setPortes = BancoDeDados.getInstance().getPortesFaixas();
            Iterator<PorteFaixa> portes = setPortes.iterator();
            PorteFaixa porte;
            while(portes.hasNext()){
                porte = portes.next();
                if(porte.isAnimalDessePorte(animal)){
                    return porte.getPorte().toString(); 
                }
            }
            throw new CadastroException();  
    }


}
