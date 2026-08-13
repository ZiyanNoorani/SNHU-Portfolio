import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 * ContactTest.java
 *
 * Unit tests verifying that the Contact class meets all five requirements:
 * contactId, firstName, lastName, phone, and address constraints.
 */
class ContactTest {

    @Test
    void testCreateValidContact() {
        Contact contact = new Contact("1234567890", "John", "Doe", "1234567890", "123 Main Street");
        assertEquals("1234567890", contact.getContactId());
        assertEquals("John", contact.getFirstName());
        assertEquals("Doe", contact.getLastName());
        assertEquals("1234567890", contact.getPhone());
        assertEquals("123 Main Street", contact.getAddress());
    }

    // --- Contact ID requirements ---

    @Test
    void testContactIdNullThrowsException() {
        assertThrows(IllegalArgumentException.class, () ->
                new Contact(null, "John", "Doe", "1234567890", "123 Main Street"));
    }

    @Test
    void testContactIdTooLongThrowsException() {
        // Boundary: 11 characters, one over the 10-character limit
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("12345678901", "John", "Doe", "1234567890", "123 Main Street"));
    }

    @Test
    void testContactIdAtMaxLengthIsValid() {
        // Boundary: exactly 10 characters should be accepted
        Contact contact = new Contact("AB12345678", "John", "Doe", "1234567890", "123 Main Street");
        assertEquals("AB12345678", contact.getContactId());
    }

    @Test
    void testContactIdIsNotUpdatable() {
        // Contact has no setContactId method, so immutability is enforced at compile time.
        // This test confirms the ID stays the same after other fields are updated.
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        contact.setFirstName("Jane");
        contact.setLastName("Smith");
        contact.setPhone("0987654321");
        contact.setAddress("456 Oak Avenue");
        assertEquals("1", contact.getContactId());
    }

    // --- First name requirements ---

    @Test
    void testFirstNameNullThrowsException() {
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", null, "Doe", "1234567890", "123 Main Street"));
    }

    @Test
    void testFirstNameTooLongThrowsException() {
        // Boundary: 11 characters, one over the 10-character limit
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "JohnJohnJoh", "Doe", "1234567890", "123 Main Street"));
    }

    @Test
    void testFirstNameAtMaxLengthIsValid() {
        // Boundary: exactly 10 characters should be accepted
        Contact contact = new Contact("1", "JohnJohnJo", "Doe", "1234567890", "123 Main Street");
        assertEquals("JohnJohnJo", contact.getFirstName());
    }

    @Test
    void testSetFirstNameUpdatesValue() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        contact.setFirstName("Jane");
        assertEquals("Jane", contact.getFirstName());
    }

    // --- Last name requirements ---

    @Test
    void testLastNameNullThrowsException() {
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", null, "1234567890", "123 Main Street"));
    }

    @Test
    void testLastNameTooLongThrowsException() {
        // Boundary: 11 characters, one over the 10-character limit
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "DoeDoeDoeDo", "1234567890", "123 Main Street"));
    }

    @Test
    void testLastNameAtMaxLengthIsValid() {
        // Boundary: exactly 10 characters should be accepted
        Contact contact = new Contact("1", "John", "DoeDoeDoeD", "1234567890", "123 Main Street");
        assertEquals("DoeDoeDoeD", contact.getLastName());
    }

    @Test
    void testSetLastNameUpdatesValue() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        contact.setLastName("Smith");
        assertEquals("Smith", contact.getLastName());
    }

    // --- Phone requirements ---

    @Test
    void testPhoneNullThrowsException() {
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "Doe", null, "123 Main Street"));
    }

    @Test
    void testPhoneTooShortThrowsException() {
        // Equivalence partition: well below the required 10 digits
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "Doe", "12345", "123 Main Street"));
    }

    @Test
    void testPhoneTooLongThrowsException() {
        // Equivalence partition: well above the required 10 digits
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "Doe", "123456789012", "123 Main Street"));
    }

    @Test
    void testPhoneNineDigitsThrowsException() {
        // Boundary: one digit short of the required 10
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "Doe", "123456789", "123 Main Street"));
    }

    @Test
    void testPhoneElevenDigitsThrowsException() {
        // Boundary: one digit over the required 10
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "Doe", "12345678901", "123 Main Street"));
    }

    @Test
    void testPhoneContainsNonDigitsThrowsException() {
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "Doe", "12345abcde", "123 Main Street"));
    }

    @Test
    void testSetPhoneUpdatesValue() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        contact.setPhone("0987654321");
        assertEquals("0987654321", contact.getPhone());
    }

    // --- Address requirements ---

    @Test
    void testAddressNullThrowsException() {
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "Doe", "1234567890", null));
    }

    @Test
    void testAddressTooLongThrowsException() {
        // Boundary: 31 characters, one over the 30-character limit
        assertThrows(IllegalArgumentException.class, () ->
                new Contact("1", "John", "Doe", "1234567890", "123 Main Street, Little Rock000"));
    }

    @Test
    void testAddressAtMaxLengthIsValid() {
        // Boundary: exactly 30 characters should be accepted
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street, Little Rock00");
        assertEquals("123 Main Street, Little Rock00", contact.getAddress());
    }

    @Test
    void testSetAddressUpdatesValue() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "123 Main Street");
        contact.setAddress("456 Oak Avenue");
        assertEquals("456 Oak Avenue", contact.getAddress());
    }
}
