const simconnect = require('./libs/simconnect');

export interface Connection {
    open(clientName: string): boolean;
    close(): void;
    mapClientEvent(id: number, name: string): boolean;
    transmitClientEvent(id: number, value: number): boolean;
    isConnected(): boolean;
    lastError(): string;
}

export const Connection: {
    new(): Connection
} = simconnect.ConnectionBindings;
