import java.util.HashMap;
import java.util.Map;

/**
 * ContactService.java
 *
 * Provides in-memory management of Contact objects, keyed by unique contact ID.
 * Supports adding, deleting, and updating contacts. No database or UI is used
 * for this milestone.
 */
public class ContactService {

    private final Map<String, Contact> contacts = new HashMap<>();

    /**
     * Adds a new contact. The contact ID must be unique.
     */
    public void addContact(Contact contact) {
        if (contact == null) {
            throw new IllegalArgumentException("Contact cannot be null");
        }
        if (contacts.containsKey(contact.getContactId())) {
            throw new IllegalArgumentException("Contact ID already exists: " + contact.getContactId());
        }
        contacts.put(contact.getContactId(), contact);
    }

    /**
     * Deletes a contact by contact ID.
     */
    public void deleteContact(String contactId) {
        if (!contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("Contact ID not found: " + contactId);
        }
        contacts.remove(contactId);
    }

    /**
     * Retrieves a contact by contact ID. Useful for tests and callers that
     * need direct access to the stored object.
     */
    public Contact getContact(String contactId) {
        Contact contact = contacts.get(contactId);
        if (contact == null) {
            throw new IllegalArgumentException("Contact ID not found: " + contactId);
        }
        return contact;
    }

    public void updateFirstName(String contactId, String firstName) {
        getContact(contactId).setFirstName(firstName);
    }

    public void updateLastName(String contactId, String lastName) {
        getContact(contactId).setLastName(lastName);
    }

    public void updatePhone(String contactId, String phone) {
        getContact(contactId).setPhone(phone);
    }

    public void updateAddress(String contactId, String address) {
        getContact(contactId).setAddress(address);
    }
}
