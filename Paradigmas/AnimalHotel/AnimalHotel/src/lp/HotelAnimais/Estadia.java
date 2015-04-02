/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.HotelAnimais;

import java.util.Date;

/**
 *
 * @author vanderson
 */
public class Estadia {

    private Animal animal;
    private Acomodacao acomodacao;
    private Date entrada;
    private int quantidadeDias=1;
    
    public Estadia(Animal animal, Acomodacao acomodacao, Date entrada, int quantidadeDias) {
        this.acomodacao = acomodacao;
        this.animal = animal;
        this.entrada = entrada;
        this.quantidadeDias = quantidadeDias;
    }

    public Animal getAnimal() {
        return animal;
    }

    public void setAnimal(Animal animal) {
        this.animal = animal;
    }

    public Acomodacao getAcomodacao() {
        return acomodacao;
    }

    public void setAcomodacao(Acomodacao acomodacao) {
        this.acomodacao = acomodacao;
    }

    public Date getEntrada() {
        return entrada;
    }

    public void setEntrada(Date entrada) {
        this.entrada = entrada;
    }

    public int getQuantidadeDias() {
        return quantidadeDias;
    }

    public void setQuantidadeDias(int quantidadeDias) {
        this.quantidadeDias = quantidadeDias;
    }
    
    public double getValor(){
        return quantidadeDias*Diaria.Grade.getPreco(acomodacao.getDimensao());
    }
    
    
}
