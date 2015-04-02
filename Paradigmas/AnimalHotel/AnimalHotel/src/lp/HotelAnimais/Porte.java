/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.HotelAnimais;

import java.util.Iterator;
import java.util.Set;
import lp.HotelCachorros.Persistencia.BancoDeDados;
import lp.HotelCachorros.Persistencia.CadastroException;

/**
 *
 * @author vanderson
 */
public enum Porte {
    Pequeno,Medio,Grande;
    
    public Porte classificarPorte(Animal animal) throws CadastroException{
            Set<PorteFaixa> setPortes = BancoDeDados.getInstance().getPortesFaixas();
            Iterator<PorteFaixa> portes = setPortes.iterator();
            PorteFaixa porte;
            while(portes.hasNext()){
                porte = portes.next();
                if(porte.isAnimalDessePorte(animal)){
                    return porte.getPorte(); 
                }
            }
            throw new CadastroException();  
    }
}
