/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.HotelAnimais;

/**
 *
 * @author vanderson
 */
public class Animal {

    private Dono dono;
    private String nome;
    private Especie especie;
    private Double altura;
    private Double comprimento;
    private Porte porte;
    private Dono responsavel2;

    public Animal(Dono dono, String nome, Especie especie, Double altura,
            Double comprimento) {
        super();
        this.dono = dono;
        this.nome = nome;
        this.especie = especie;
        this.altura = altura;
        this.comprimento = comprimento;
    }
    
    //métodos get e set
    public Dono getDono() {
        return dono;
    }

    public void setDono(Dono dono) {
        this.dono = dono;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Especie getEspecie() {
        return especie;
    }

    public void setEspecie(Especie especie) {
        this.especie = especie;
    }

    public Double getAltura() {
        return altura;
    }

    public void setAltura(Double altura) {
        this.altura = altura;
    }

    public Double getComprimento() {
        return comprimento;
    }

    public void setComprimento(Double comprimento) {
        this.comprimento = comprimento;
    }

    public Porte getPorte() {
        return porte;
    }

    public void setPorte(Porte porte) {
        this.porte = porte;
    }

    public Dono getResponsavel2() {
        return responsavel2;
    }

    public void setResponsavel2(Dono responsavel2) {
        this.responsavel2 = responsavel2;
    }
    
    
}
