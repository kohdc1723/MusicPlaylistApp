#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TITLE_SIZE 80
#define ARTIST_SIZE 80

typedef struct Playlist {
    char* title;
    char* artist;
    struct Playlist* prev;
    struct Playlist* next;
} Playlist;

void addSong(Playlist** plHead, char* title, char* artist);
void currentSong(Playlist* plHead);
void searchSong(Playlist** plHead, const char* title);
void displayPlaylist(Playlist* plHead);
void displayReversePlaylist(Playlist* plHead);
void nextSong(Playlist* plHead);
void previousSong(Playlist* plHead);
void deleteSong(Playlist** plHead, const char* title);
void mallocCheck(void* check);
void setNewMusicDetails(Playlist* newMusic, char* title, char* artist);
void deleteOnlySong(Playlist** plHead, Playlist* temp, const char* title);
void deleteFirstSong(Playlist** plHead, Playlist* temp, const char* title);
void deleteMiddleSong(Playlist* temp, const char* title);
void deleteLastSong(Playlist* temp, const char* title);
void deleteByCase(Playlist** plHead, Playlist* temp, const char* title);

int main(void) {
    Playlist* album = NULL;
    addSong(&album, "Memories", "Maroon 5");
    addSong(&album, "With or Without You", "U2");
    addSong(&album, "Nothing Else Matters", "Metallica");
    addSong(&album, "Maki Madni", "The Derek Trucks Band");
    addSong(&album, "Summer of 69", "Bryan Adams");
    addSong(&album, "Another Brick in the Wall", "Pink Floyd");

    displayReversePlaylist(album);
    displayPlaylist(album);

    currentSong(album);
    nextSong(album);
    previousSong(album);
    searchSong(&album, "Ideal 30 days");
    searchSong(&album, "Maki Madni");
    deleteSong(&album, "Memories");

    return 0;
}

void addSong(Playlist** plHead, char* title, char* artist) {
    Playlist* newMusic = (Playlist*) malloc(sizeof(Playlist));
    mallocCheck((Playlist*) newMusic);
    setNewMusicDetails(newMusic, title, artist);

    newMusic->next = NULL;
    if (*plHead == NULL) {
        newMusic->prev = NULL;
        *plHead = newMusic;
        return;
    }

    Playlist* last = *plHead;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newMusic;
    newMusic->prev = last;
}

void currentSong(Playlist* plHead) {
    if (plHead == NULL) {
        printf("Current Song: End of Playlist\n");
    } else {
        printf("Current Song: %s, %s\n", plHead->title, plHead->artist);
    }
}

void searchSong(Playlist** plHead, const char* title) {
    Playlist* temp = (*plHead);
    if (temp == NULL) {
        printf("Searched Song: %s, Does not exist\n", title);
    } else {
        while (temp != NULL) {
            if (strcmp(temp->title, title) == 0) {
                printf("Searched Song: %s, %s\n", temp->title, temp->artist);
                return;
            }
            temp = temp->next;
        }
        printf("Searched Song: %s, Does not exist\n", title);
    }
}

void displayPlaylist(Playlist* plHead) {
    Playlist* temp = plHead;
    printf("<< Playlist >>\n");
    if (temp == NULL) {
        printf("Playlist is empty\n");
        return;
    }
    while (temp != NULL) {
        printf("%s, %s\n", temp->title, temp->artist);
        temp = temp->next;
    }
    printf("\n");
}

void displayReversePlaylist(Playlist* plHead) {
    Playlist* temp = plHead;
    printf("<< Playlist in Reverse >>\n");
    if (temp == NULL) {
        printf("Playlist is empty\n");
        return;
    }
    Playlist* last;
    while (temp != NULL) {
        last = temp;
        temp = temp->next;
    }
    while (last != NULL) {
        printf("%s, %s\n", last->title, last->artist);
        last = last->prev;
    }
    printf("\n");
}

void nextSong(Playlist* plHead) {
    if (plHead == NULL) {
        printf("Next Song: Playlist is empty\n");
    } else {
        if (plHead->next == NULL) {
            printf("Next Song: End of Playlist\n");
        } else {
            printf("Next Song: %s, %s\n", plHead->next->title, plHead->next->artist);
        }
    }
}

void previousSong(Playlist* plHead) {
    if (plHead == NULL) {
        printf("Previous Song: Playlist is empty\n");
    } else {
        if (plHead->prev == NULL) {
            printf("Previous Song: End of Playlist\n");
        } else {
            printf("Previous Song: %s, %s\n", plHead->prev->title, plHead->prev->artist);
        }
    }
}

void deleteSong(Playlist** plHead, const char* title) {
    Playlist* temp = *plHead;
    Playlist* target = NULL;
    if (temp == NULL) {
        printf("Delete Song: Playlist is empty\n");
        return;
    }
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            target = temp;
            break;
        }
        temp = temp->next;
    }
    if (target == NULL) {
        printf("Delete Song: \"%s\" is not found\n", title);
        return;
    }
    deleteByCase(plHead, temp, title);
}

void deleteByCase(Playlist** plHead, Playlist* temp, const char* title) {
    if (temp->prev == NULL && temp->next == NULL) {
        deleteOnlySong(plHead, temp, title);
        return;
    }
    if (temp->prev == NULL && temp->next != NULL) {
        deleteFirstSong(plHead, temp, title);
        return;
    }
    if (temp->prev != NULL && temp->next != NULL) {
        deleteMiddleSong(temp, title);
        return;
    }
    if (temp->prev != NULL && temp->next == NULL) {
        deleteLastSong(temp, title);
        return;
    }
}

void deleteOnlySong(Playlist** plHead, Playlist* temp, const char* title) {
    *plHead = NULL;
    free(temp->title);
    free(temp->artist);
    free(temp);
    printf("Song Deleted: %s\n", title);
}

void deleteFirstSong(Playlist** plHead, Playlist* temp, const char* title) {
    temp->next->prev = NULL;
    *plHead = temp->next;
    free(temp->title);
    free(temp->artist);
    free(temp);
    printf("Song Deleted: %s\n", title);
}

void deleteMiddleSong(Playlist* temp, const char* title) {
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp->title);
    free(temp->artist);
    free(temp);
    printf("Song Deleted: %s\n", title);
}

void deleteLastSong(Playlist* temp, const char* title) {
    temp->prev->next = NULL;
    free(temp->title);
    free(temp->artist);
    free(temp);
    printf("Song Deleted: %s\n", title);
}

void mallocCheck(void* check) {
    if (check == NULL) {
        printf("No memory is allocated!\n");
        exit(0);
    }
}

void setNewMusicDetails(Playlist* newMusic, char* title, char* artist) {
    newMusic->title = (char*) malloc(sizeof(char) * TITLE_SIZE);
    mallocCheck((char*) newMusic->title);
    strcpy(newMusic->title, title);

    newMusic->artist = (char*) malloc(sizeof(char) * ARTIST_SIZE);
    mallocCheck((char*) newMusic->artist);
    strcpy(newMusic->artist, artist);
}