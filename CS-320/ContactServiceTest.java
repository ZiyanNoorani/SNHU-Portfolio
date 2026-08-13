import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 * ContactServiceTest.java
 *
 * Unit tests verifying that the ContactService class meets all three requirements:
 * add contacts with a unique ID, delete contacts by ID, and update contact fields by ID.
 */
class ContactServiceTest {

    private ContactService service;

    @BeforeEach
    void setUp() {
        service = new ContactService();
    }

    // --- Add requirement ---

    @Test
    void testAddContact() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        service.addContact(contact);
        assertEquals(contact, service.getContact("1"));
    }

    @Test
    void testAddContactWithDuplicateIdThrowsException() {
        Contact contact1 = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        Contact contact2 = new Contact("1", "Jane", "Smith", "0987654321", "456 Oak Avenue");
        service.addContact(contact1);
        assertThrows(IllegalArgumentException.class, () -> service.addContact(contact2));
    }

    @Test
    void testAddNullContactThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> service.addContact(null));
    }

    // --- Delete requirement ---

    @Test
    void testDeleteContact() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        service.addContact(contact);
        service.deleteContact("1");
        assertThrows(IllegalArgumentException.class, () -> service.getContact("1"));
    }

    @Test
    void testDeleteNonExistentContactThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> service.deleteContact("nonexistent"));
    }

    // --- Update requirement ---

    @Test
    void testUpdateFirstName() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        service.addContact(contact);
        service.updateFirstName("1", "Jane");
        assertEquals("Jane", service.getContact("1").getFirstName());
    }

    @Test
    void testUpdateLastName() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        service.addContact(contact);
        service.updateLastName("1", "Smith");
        assertEquals("Smith", service.getContact("1").getLastName());
    }

    @Test
    void testUpdatePhone() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        service.addContact(contact);
        service.updatePhone("1", "0987654321");
        assertEquals("0987654321", service.getContact("1").getPhone());
    }

    @Test
    void testUpdateAddress() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        service.addContact(contact);
        service.updateAddress("1", "456 Oak Avenue");
        assertEquals("456 Oak Avenue", service.getContact("1").getAddress());
    }

    @Test
    void testUpdateOnNonExistentContactThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> service.updateFirstName("nonexistent", "Jane"));
    }

    @Test
    void testUpdateWithInvalidValueThrowsException() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        service.addContact(contact);
        assertThrows(IllegalArgumentException.class, () -> service.updateFirstName("1", "JohnJohnJohn"));
    }
}
