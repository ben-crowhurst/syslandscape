# Components #

## HTTP ##

HTTP is a set of low-level component handling HTTP communication.

### HTTP Server  ###

Component is responsible for accepting connections, read / write available data from these connections and pass execution to HTTPHandler.

### HTTP Handler ###

Component is responsible for forwarding execution to Web Components.

### HTTP Request Parser ###

Parser is reading HTTP message request headers and body in a secure and fast manner. 

Implementation is taken from 
[nodejs/http-parser](https://github.com/nodejs/http-parser). It's 
added as external git dependency into external/http-parser. Actually
source code is copied to syslandscape/web

# Hypertext Transfer Protocol (HTTP/1.1) #

## RFCs ##
Original HTTP / 1.1 [RFC](https://www.w3.org/Protocols/rfc2616/rfc2616.html) is replaced by multipile RFCs (7230-7237):

* [RFC7230](https://tools.ietf.org/html/rfc7230) - Message Syntax and Routing. An overview of HTTP architecture and its associated terminology, defines the "http" and "https" Uniform Resource Identifier (URI) schemes, defines the HTTP/1.1 message syntax and parsing requirements, and describes related security concerns for implementations.
* [RFC7231](https://tools.ietf.org/html/rfc7231) - Semantics and Content. Defines the semantics of HTTP/1.1 messages, as expressed by request methods, request header fields, response status codes, and response header fields, along with the payload of messages (metadata and body content) and mechanisms for content negotiation.
* [RFC7232](https://tools.ietf.org/html/rfc7232) - Conditional Requests. Defines HTTP/1.1 conditional requests, including metadata header fields for indicating state changes, request header fields for making preconditions on such state, and rules for constructing the responses to a conditional request when one or more preconditions evaluate to false.
* [RFC7233](https://tools.ietf.org/html/rfc7233) - Range Requests. Defines range requests and the rules for constructing and combining responses to those requests.
* [RFC7234](https://tools.ietf.org/html/rfc7234) - Caching. Defines HTTP caches and the associated header fields that control cache behavior or indicate cacheable response messages.
* [RFC7235](https://tools.ietf.org/html/rfc7235) - Authentication. Defines the HTTP Authentication framework.
* [RFC7236](https://tools.ietf.org/html/rfc7236) - Authentication Scheme Registrations. Registers Hypertext Transfer Protocol (HTTP) authentication schemes that have been defined in RFCs before the IANA HTTP Authentication Scheme Registry was established.
* [RFC7237](https://tools.ietf.org/html/rfc7237) - Method Registrations. Registers those Hypertext Transfer Protocol (HTTP) methods that have been defined in RFCs before the IANA HTTP Method Registry was established.
* [RFC6265](https://tools.ietf.org/html/rfc6265) - HTTP State Management Mechanism.

## State Management ##

Although simple on their surface, cookies have a number of complexities.  For example, the server indicates a scope for each cookie when sending it to the user agent.  The scope indicates the maximum amount of time in which the user agent should return the cookie, the servers to which the user agent should return the cookie, and the URI schemes for which the cookie is applicable. 

For historical reasons, cookies contain a number of security and privacy infelicities.  For example, a server can indicate that a given cookie is intended for "secure" connections, but the Secure attribute does not provide integrity in the presence of an active network attacker.  Similarly, cookies for a given host are shared across all the ports on that host, even though the usual "same-origin policy" used by web browsers isolates content retrieved via different ports.

