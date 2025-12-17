# Roles and Responsibilities

This document defines the roles, activities and responsibilities within the RDK HAL ecosystem.

!!! note
    Where "Comcast" is used it can mean either a Sky or Comcast team. We are all in it together...

## The Vendor (OEM)

The Vendor, which may be better understood as the Original Equipment Manufacturer (OEM), is the integrator responsible for delivering an integrated and tested SoC and Board SW delivery.

**Key Responsibilities:**

* Integrates 3rd party SW and RDK SW components that have a SoC or Board related configuration/build
* The Vendor can be a 3rd party or internal to Comcast when integrating a "home grown product"

## Vendor Layer Owner

The Vendor Layer Owner acts as the single point of contact for the delivery and quality of a Vendor Layer. This role can be fulfilled by Comcast or 3rd party organisations.

**Key Responsibilities:**

* Single point of contact for the delivery and quality of a Vendor Layer
* Expected to ensure VTS is executed and passes where appropriate
* The Vendor Layer Owner can be both the 3rd party or internal to Comcast when integrating a "home grown product"
* The Vendor Owner can be responsible for one or more Vendor Layers

## Vendor Layer Ingestion (Comcast Specific)

The process of ingesting a new or changed Vendor Layer into a Comcast Product (or product Comcast is responsible for).

## Vendor Layer Ingestion Owner (Comcast Specific)

**Key Responsibilities:**

* Single point of contact and total responsibility for the ingestion of a new or changed Vendor Layer into a Comcast Product
* Responsible for ensuring that all quality requirements have been passed before wider use
* Expected to ensure VTS is executed and passes where appropriate
* Where the Vendor Layer Owner is internal, the Vendor Layer and Ingestion Owner are one and the same and from a Comcast perspective the Ingestion Owner IS the Vendor Layer Owner

## Vendor Test Delivery Team (Comcast HAL Police)

**Key Responsibilities:**

* Responsible for the management and delivery of the HAL Test Infrastructure
* Ensuring HAL governance is enforced
* Coordinate with other testing teams
