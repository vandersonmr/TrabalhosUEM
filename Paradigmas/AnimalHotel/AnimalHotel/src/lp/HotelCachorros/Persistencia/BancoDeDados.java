/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.HotelCachorros.Persistencia;

import lp.HotelAnimais.Diaria;
import lp.HotelAnimais.Estadia;
import lp.HotelAnimais.PorteFaixa;
import lp.HotelAnimais.Pessoa;
import lp.HotelAnimais.Especie;
import lp.HotelAnimais.Acomodacao;
import lp.HotelAnimais.Animal;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class BancoDeDados {

    private Set<Acomodacao> acomodacoes;
    private Set<Animal> animais;
    private Set<Diaria> diarias;
    private Set<Pessoa> pessoas;
    private Set<Especie> especies;
    private Set<Estadia> estadias;
    private Set<PorteFaixa> portesFaixas;
    private static BancoDeDados instance;

    private BancoDeDados() {
        acomodacoes = new HashSet<>();
        animais = new HashSet<>();
        diarias = new HashSet<>();
        pessoas = new HashSet<>();
        especies = new HashSet<>();
        estadias = new HashSet<>();
        portesFaixas = new HashSet<>();
    }

    public static BancoDeDados getInstance() {
        if (instance == null) {
            instance = new BancoDeDados();
        }
        return instance;
    }

    public Set<Acomodacao> getAcomodacoes() {
        return acomodacoes;
    }

    public Set<Animal> getAnimais() {
        return animais;
    }

    public Set<Diaria> getDiarias() {
        return diarias;
    }

    public Set<Pessoa> getPessoas() {
        return pessoas;
    }

    public Set<Especie> getEspecies() {
        return especies;
    }

    public Set<Estadia> getEstadias() {
        return estadias;
    }

    public Set<PorteFaixa> getPortesFaixas() {
        return portesFaixas;
    }
    
    public Estadia getEstadia(Animal animal){
         Iterator i = BancoDeDados.getInstance().getEstadias().iterator();
        while (i.hasNext()) {
            Estadia estadia = (Estadia) i.next();
            if (estadia.getAnimal().equals(animal)) {
                return estadia;
            }
        }
        return null;
        
    }
    
    public Animal getAnimal(String nome) {
        Iterator i = BancoDeDados.getInstance().getAnimais().iterator();
        while (i.hasNext()) {
            Animal animal = (Animal) i.next();
            if (animal.getNome().equals(nome)) {
                return animal;
            }
        }
        return null;
    }

    
}