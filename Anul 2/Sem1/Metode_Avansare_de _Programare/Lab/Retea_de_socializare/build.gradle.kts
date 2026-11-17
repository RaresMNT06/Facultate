plugins {
    id("java")
}

group = "retea"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    // driverul JDBC pentru PostgreSQL (laboratorul 5)
    implementation("org.postgresql:postgresql:42.7.7")
}