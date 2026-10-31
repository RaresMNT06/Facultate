package repository.file;

import exceptions.RepositoryException;
import exceptions.ValidationException;
import model.Entity;
import repository.InMemoryRepository;
import repository.Repository;
import validators.Validator;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.time.format.DateTimeParseException;



/**
 * Repository care pastreaza entitatile in memorie si le salveaza intr-un fisier.
 * Template Method: algoritmul de citire/scriere este fix, iar conversia
 * linie - entitate este lasata subclaselor.
 *
 * @param <ID> tipul identificatorului
 * @param <E>  tipul entitatilor
 */

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {

    private final String fileName;

    /**
     * @param validator strategia de validare
     * @param fileName  calea catre fisier
     */
    public AbstractFileRepository(Validator<E> validator, String fileName) {
        super(validator);
        this.fileName = fileName;
        loadData();
    }


    /**
     * Transforma o linie din fisier intr-o entitate.
     *
     * @param line linia citita
     * @return entitatea creata
     */
    protected abstract E extractEntity(String line);


    /**
     * Transforma o entitate intr-o linie de fisier.
     *
     * @param entity entitatea de scris
     * @return linia corespunzatoare
     */
    protected abstract String createEntityAsString(E entity);

    /**
     * citeste toate liniile din fisier si salveaza entitatile in memorie;
     * daca fisierul nu exista, repository-ul porneste gol;
     * o linie corupta sau invalida este raportata (numarul liniei si motivul) si ignorata
     *
     * @throws RepositoryException daca fisierul exista, dar nu poate fi citit
     */
    private void loadData() {
        File file = new File(fileName);
        if (!file.exists()) {
            System.out.println("File " + fileName + " does not exist; the repository starts empty.");
            return;
        }
        try (BufferedReader reader = new BufferedReader(new FileReader(file, StandardCharsets.UTF_8))) {
            String line;
            int lineNumber = 0;
            while ((line = reader.readLine()) != null) {
                lineNumber++;
                if (line.isBlank()) {
                    continue;
                }
                try {
                    E entity = parseLine(line);
                    if (super.save(entity) != null) {
                        System.out.println("Warning: " + fileName + ", line " + lineNumber
                                + " ignored: duplicate id " + entity.getId());
                    }
                } catch (RepositoryException | ValidationException e) {
                    System.out.println("Warning: " + fileName + ", line " + lineNumber
                            + " ignored: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            throw new RepositoryException("Cannot read file " + fileName, e);
        }
    }

    /**
     * transforma o linie in entitate; erorile de format sunt impachetate intr-o RepositoryException
     *
     * @param line - linia de transformat
     * @return entitatea descrisa de linie
     * @throws RepositoryException daca linia nu are formatul corect (exceptia originala este pastrata ca cauza)
     */
    private E parseLine(String line) {
        try {
            return extractEntity(line);
        } catch (NumberFormatException | DateTimeParseException | ArrayIndexOutOfBoundsException e) {
            throw new RepositoryException("invalid format (" + e.getMessage() + ")", e);
        }
    }

    /**
     * rescrie tot fisierul cu entitatile din memorie; creeaza folderul daca nu exista
     *
     * @throws RepositoryException daca fisierul nu poate fi scris
     */
    private void writeToFile() {
        File file = new File(fileName);
        File folder = file.getParentFile();
        if (folder != null && !folder.exists()) {
            folder.mkdirs();
        }
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file, StandardCharsets.UTF_8))) {
            for (E entity : findAll()) {
                writer.write(createEntityAsString(entity));
                writer.newLine();
            }
        } catch (IOException e) {
            throw new RepositoryException("Cannot write file " + fileName, e);
        }
    }


    /**
     * salveaza entitatea in memorie si, daca a fost salvata, rescrie fisierul
     *
     * @param entity - entitatea de salvat; nu poate fi null
     * @return null - daca entitatea a fost salvata, altfel entitatea (id-ul exista deja)
     * @throws ValidationException      daca entitatea nu este valida
     * @throws IllegalArgumentException daca entitatea este null
     * @throws RepositoryException      daca fisierul nu poate fi scris
     */
    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if(result == null){
            writeToFile();
        }
        return result;
    }


    /**
     * sterge entitatea din memorie si, daca a existat, rescrie fisierul
     *
     * @param id - id-ul entitatii de sters; nu poate fi null
     * @return entitatea stearsa sau null daca nu exista
     * @throws IllegalArgumentException daca id-ul este null
     * @throws RepositoryException      daca fisierul nu poate fi scris
     */
    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if(result != null){
            writeToFile();
        }
        return result;
    }


    /**
     * actualizeaza entitatea in memorie si, daca a fost actualizata, rescrie fisierul
     *
     * @param entity - entitatea cu datele noi; nu poate fi null
     * @return null - daca entitatea a fost actualizata, altfel entitatea (id-ul nu exista)
     * @throws ValidationException      daca entitatea nu este valida
     * @throws IllegalArgumentException daca entitatea este null
     * @throws RepositoryException      daca fisierul nu poate fi scris
     */
    @Override
    public E update(E entity) {
        E result = super.update(entity);
        if(result == null){
            writeToFile();
        }
        return result;
    }
}
