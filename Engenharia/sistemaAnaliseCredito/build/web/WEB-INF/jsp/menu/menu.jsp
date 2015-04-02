<%-- 
    Document   : menu
    Created on : 16/05/2013, 18:36:04
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>

    <style>
        @import url("/WEB-INF/style.css");
    </style>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Sistema de Análise de Crédito</title>
    </head>

    <body>

        <ul id="menu">
            <li>
                <a href="${pageContext.request.contextPath}/menu">Home</a>
            </li>
            <li>
                <a>Consultas</a>
                <ul>
                    <li>
                        <a href="${pageContext.request.contextPath}/menuConsultaInterna">Consulta estatística</a>
                    </li>
                    <li>
                        <a href="${pageContext.request.contextPath}/menuConsultaExterna">Consultar inadimplência</a>
                    </li>
                </ul>
            <li>
            <li>
                <a href="${pageContext.request.contextPath}/gerarBoleto">Gerar Boleto</a>
            <li>
            <li>
                <a >Gerenciamento de Lojista</a>
                <ul>
                    <li><a href="${pageContext.request.contextPath}/menuNovoCadastro">Novo Cadastro</a></li>
                    <li><a href="${pageContext.request.contextPath}/menuBuscarCadastro">Buscar Cadastro</a></li>
                    <!--<li><a href="${pageContext.request.contextPath}/menuAlterarCadastro">Altera Cadastro</a></li>-->
                </ul>
            <li>
            <li>
                <a href="${pageContext.request.contextPath}/logout">Logout</a>
            <li><br><br>
            <li><a href="ajuda.html">Ajuda</a></li>
        </ul>

    <center>  

            <fieldset>
                <legend><h1>BEM VINDO AO SISTEMA DE ANÁLISE DE CRÉDITO DA A.R.I Inc</h1></legend>
                <br><br>
         
                <form action="${pageContext.request.contextPath}/menuConsultaInterna">
                    <input type="submit"  class="btn" value="Consulta estatística"/>
                </form>
                    
                <br><br><br>
                <form action="${pageContext.request.contextPath}/gerarBoleto">
                    <input type="submit"  class="btn" value="Gera Boleto" />
                </form>
                <br>
                <form action="${pageContext.request.contextPath}/menuNovoCadastro">
                    <input type="submit" class="btn" value="Cadastro de Lojista" />
                </form><br>
                <form action="ajuda.html">
                    <input type="submit" class="btn" value="Ajuda" />
                </form>
                <br><br>
                Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.
            </fieldset>

    </body>
</html>
