/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.HotelAnimais;

/**
 *
 * @author vanderson
 */
public enum Diaria {

    Pequena,
    Media,
    Grade;
    
    
    public double getPreco(Porte p){
        return getPreco(getDiaria(p));
    }
    
    private double getPreco(Diaria d) {
             switch(d){
                 case Grade:
                     return 100d;
                 case Media:
                     return 60d;
                 case Pequena:
                     return 40d;
             }
        return 0;
    }
    
    private Diaria getDiaria(Porte porte){
        switch(porte){
            case Grande:
                return Grade; 
            case Medio:
                return Media;
            case Pequeno:
                return Pequena;
        }
        return null;
    }

}
